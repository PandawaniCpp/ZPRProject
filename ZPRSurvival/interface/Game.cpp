/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Game.h"

// #TITLE
std::string Game::TITLE = "#TITLE";

Game::Game () {
	// All we need to play.
	GraphicsOptions::init ();
	gameWindow = new sf::RenderWindow (GraphicsOptions::videoMode, Game::TITLE, GraphicsOptions::videoStyle);	// Create new Window
	console = new Console ();
	worldMap = new WorldMapView (time(NULL), 0.65, 5000.0, 8, 5000, 5000);

	// sf::View init.
	worldView = gameWindow->getDefaultView ();
	worldView.setCenter (5000.f, 5000.f);		// #SETSPAWN
	gameWindow->setView (worldView);
	worldViewPosition = sf::Vector2f (worldView.getCenter().x - worldView.getSize().x / 2.f,
									  worldView.getCenter ().y - worldView.getSize ().y / 2.f);

	state = GameState::INIT;		// Proper first state
}

Game::~Game () {
	delete gameWindow;

	// Scene graph's destructor deallocates all graph's objects (all views).
	// #TODO CHECK THIS
}

void Game::initialize () {
	gameWindow->setKeyRepeatEnabled (false);			// Prevents from unintended key repetition

	// Initialize factory with prefabs and keyboard interface with key mappings.
	EntityFactory::prefabInit ();
	KeyboardInterface::assignKeys ();
	KeyboardInterface::assignActions ();
	
	// Set fonts
	fontHolder.load (Fonts::F_MENU, "resources/segoeuil.ttf");
	fontHolder.load (Fonts::F_CONSOLE, "resources/droidmono.ttf");

	// World information 
	// #TODO Delete this crap?
	worldBounds.top = worldBounds.left = 0.f;	// Top left corner (0, 0)
	worldBounds.height = 10000;					// World size
	worldBounds.width = 10000;					// #TODO put proper numbers from WorldMap

	// Center the sf::View to player position.
	worldView.setCenter (worldMap->getSpawnPoint());	

	// Initialize entities
	entitiesInit ();
	
	// Initialize main layers.
	layersInit ();

	// Set default parameters of objects owned.
	objectsInit ();

	// Set default game options.
	applyOptions ();

	// If everything's fine, move on to the next state.
	this->state = GameState::IN_MENU;
}

void Game::run () {
	// Calculates time difference between frames and corrects occasional lags (if occured).
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	timeSinceLastUpdate += clock.restart ();
	PlayerController::deltaTime = timePerFrame;

	// Start the Game
	state = GameState::PLAYING;
	
	// Main game loop (handle events -> update everything -> render eveything)
	while (gameWindow->isOpen ()) {
		processEvents ();
		timeSinceLastUpdate += clock.restart ();			// This whole idea is to protect...

		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			processEvents ();

			if (state == GameState::EXIT)
				gameWindow->close ();

			update ();										//...game from lags' consequences. 
		}
		render ();

		// Calculate and show the fps value of the previous frame
		currentFPS = 1000.f / clock.getElapsedTime ().asMilliseconds();
		console->update ("fps", std::max(currentFPS, (float)GraphicsOptions::fps));
		console->draw (gameWindow);
	}
}

void Game::terminate () {

}


void Game::entitiesInit () {
	playerController.createEntity (Entities::PLAYER, Textures::P_IDLE, sf::Vector2f (5000.f, 5000.f), sf::Vector2i (50,50));		// #SETSPAWN
	itemController.createEntity (Entities::WALL, Textures::I_WALL, sf::Vector2f (4500.f, 5000.f), sf::Vector2i(450, 300));
}

void Game::layersInit () {
	// Initialize game scene graph
	for (std::size_t i = 0; i < LAYER_COUNT; ++i) {
		GameObject::ObjectPtr layer (new GameObject ());
		sceneLayers[i] = layer.get ();
		sceneGraph.attachChild (layer);
	}

	// Attach map, console and player to game layers
	sceneLayers[Game::CONSOLE]->attachChild (GameObject::ObjectPtr (console));
	sceneLayers[Game::MAP]->attachChild (GameObject::ObjectPtr (worldMap));
	sceneLayers[Game::PLAYER]->attachChild (GameObject::ObjectPtr (playerController[0]));
	sceneLayers[Game::ITEMS]->attachChild (GameObject::ObjectPtr (itemController[0]));

}

void Game::objectsInit () {
	// Set default console's parameters
	console->insert ("fps", currentFPS);
	console->insert ("x", 0);
	console->insert ("y", 0);
	console->insert ("direction", 0);
	console->insert ("rotation", 0);
	console->insert ("current resolution", GraphicsOptions::getCurrentResolution ());
	console->insert ("b2Body counter", 0);
	console->insert ("avail. resolutions", GraphicsOptions::getResolutionsAvailable ());
	console->setFont (fontHolder.get (Fonts::F_CONSOLE));
}

void Game::applyOptions () {
	timePerFrame = sf::seconds (1.f / GraphicsOptions::fps);			// Static frame, (1 / x) = x fps.
	GraphicsOptions::vSyncOn ? gameWindow->setVerticalSyncEnabled (true) : gameWindow->setVerticalSyncEnabled (false);

	if (state != GameState::INIT)
		gameWindow->create (GraphicsOptions::videoMode, Game::TITLE, GraphicsOptions::videoStyle);
	console->update ("current resolution", GraphicsOptions::getCurrentResolution());

	// Set scaling for new resolution ratio
	//

	// #TODO Do we need this?
	// If needed, set black stripes at the top and bottom of the screen
	//

	// Update sf::View
	worldView = gameWindow->getDefaultView ();
	worldView.setCenter (playerController[0]->getPosition ());
	gameWindow->setView (worldView);
	worldViewPosition = sf::Vector2f (worldView.getCenter ().x - worldView.getSize ().x / 2.f,
									  worldView.getCenter ().y - worldView.getSize ().y / 2.f);
}

void Game::processEvents () {
	// Capture and process mouse position
	MouseInterface::capturePosition (*gameWindow);
	MouseInterface::calculatePlayerOffset (playerController[0]->getPosition () - worldViewPosition);
	playerController[0]->setTargetRotation (MouseInterface::calculateRotation());		// We know it's player, no need to set up a rotation command.
	worldView.setCenter (playerController[0]->getPosition () + MouseInterface::playerOffset);
	gameWindow->draw (*playerController[0]);

	// Handle keyboard input.
	sf::Event event;
	
	// Catch event.
	while (gameWindow->pollEvent (event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				commandQueue.push (KeyboardInterface::pressedKeyHandle (state, event.key.code));
				break;
			case sf::Event::KeyReleased:
				commandQueue.push (KeyboardInterface::releasedKeyHandle (state, event.key.code));
				break;
			case sf::Event::Closed:
				gameWindow->close ();
				break;
			default:
				break;
		}
	}
}

void Game::commandInterpret () {
	while (!commandQueue.isEmpty ()) {
		Command * command = commandQueue.pop ();
		if (command->commandType == Commands::NONE) {
			delete command;
			continue;
		}
		if (command->category == Entities::NONE) {
			gameCommandExecute (command);
		}
		else {
			sceneGraph.passCommand (command, PlayerController::deltaTime);
		}
	}
}

void Game::gameCommandExecute (Command * command) {
	// Combination of special keys pressed at that moment.
	int specialKeys = sf::Keyboard::isKeyPressed (sf::Keyboard::LShift) * KeyboardInterface::SHIFT +
					sf::Keyboard::isKeyPressed (sf::Keyboard::LControl) * KeyboardInterface::CONTROL +
					sf::Keyboard::isKeyPressed (sf::Keyboard::LAlt) * KeyboardInterface::ALT +
					sf::Keyboard::isKeyPressed (sf::Keyboard::LSystem) * KeyboardInterface::SYSTEM;

	// Check every game command
	if (command->commandType == Commands::G_EXIT)	// Game termination
		gameWindow->close ();
	else if (command->commandType == Commands::CON_TRIGGER)		// Show/Hide Console
		Console::visible = !Console::visible;
	else if (command->commandType == Commands::RES_UP) {		// Increase resolution
		if (Console::visible && command->specialKeys == specialKeys) {
			GraphicsOptions::switchResolution (true);
			applyOptions ();
		}
	}
	else if (command->commandType == Commands::RES_DOWN) {		// Decrease resolution
		if (Console::visible && command->specialKeys == specialKeys) {
			GraphicsOptions::switchResolution (false);
			applyOptions ();
		}
	}
	else if (command->commandType == Commands::SET_FULLSCREEN) {	// Turn fullscreen on/off
		if (Console::visible && command->specialKeys == specialKeys) {
			if (GraphicsOptions::fullscreenModeOn)
				setFullscreenEnabled (false);
			else
				setFullscreenEnabled (true);
		}
	}
	else if (command->commandType == Commands::SAVE_MAP_TO_IMG) {	// Save map to png file.
		if (Console::visible && command->specialKeys == specialKeys)
			worldMap->getMapImage ().saveToFile ("./resources/zrzut_mapy.png");
	}
}

void Game::update () {
	worldViewPosition = sf::Vector2f (worldView.getCenter ().x - worldView.getSize ().x / 2.f,
									  worldView.getCenter ().y - worldView.getSize ().y / 2.f);

	worldMap->t += rand()%750/100000.0;

	// Calculate player-mouse offset.		#TODO REMOVE?
	//MouseInterface::calculatePlayerOffset (playerController[0]->getPosition () - worldViewPosition);

	//// Pass target rotation to player.
	//float mouseRotation = MouseInterface::calculateRotation ();
	//playerController[0]->setTargetRotation (mouseRotation);		// We know it's player, no need to set up a rotation command.

	// Process to taking commands from CommandQueue
	commandInterpret ();

	// Update player.
	playerController.update ();
	itemController.updateEntities ();

	// Apply physics to b2World
	Player::boxWorld.Step (1.0 / GraphicsOptions::fps, 8, 3);

	// Update console ouput.
	console->update ("x", playerController[0]->getPosition ().x);
	console->update ("y", playerController[0]->getPosition ().y);
	console->update ("direction", (float)playerController[0]->direction);
	console->update ("rotation", playerController[0]->boxBody->GetAngle () * RAD_TO_DEG);
	console->update ("mouse rotation", MouseInterface::calculateRotation () * RAD_TO_DEG);
	console->update ("force x", playerController[0]->boxBody->GetForce().x);
	console->update ("force y", playerController[0]->boxBody->GetForce().y);
	console->update ("velocity x", playerController[0]->boxBody->GetLinearVelocity ().x);
	console->update ("velocity y", playerController[0]->boxBody->GetLinearVelocity ().y);
	console->update ("b2Body counter", Player::boxWorld.GetBodyCount ());

	// Set the world displacement vector relatively to player.
	//worldView.setCenter (playerController[0]->getPosition () + MouseInterface::playerOffset);
	//worldView.setRotation (45.f);
	gameWindow->setView (worldView);

	// Vector for displacement correction.
	sf::Vector2f vec (worldView.getCenter () - worldView.getSize () / 2.0f);

	// Correct console displacement (always in top-left corner).
	console->setPosition (worldViewPosition);

	// Correct map displacement.
	worldMap->setPosition (vec);
	//vec.y -= worldMap->getWorldBounds().y - GraphicsOptions::videoMode.height;		// !!!!!
	worldMap->setViewPosition (vec);	
	worldMap->update();
}

void Game::render () {
	gameWindow->clear ();		// Clear eveything.
	draw ();
	gameWindow->display ();
}

void Game::draw () {
	// Draw all layers in order.
	sceneGraph.drawAll (gameWindow);
}

void Game::attachChild (GameObject::ObjectPtr * shPtr, Game::Layer layer) {
	GameObject::ObjectPtr ptrLayer (*shPtr);
	sceneLayers[layer]->attachChild (ptrLayer);
}

void Game::setFullscreenEnabled (bool enable) {
	if (enable) {
		gameWindow->create (GraphicsOptions::videoMode, "ZPR Survival", sf::Style::Fullscreen);
		GraphicsOptions::videoStyle = sf::Style::Fullscreen;
	}
	else {
		gameWindow->create (GraphicsOptions::videoMode, "ZPR Survival", sf::Style::Close | sf::Style::Titlebar);
		GraphicsOptions::videoStyle = sf::Style::Close | sf::Style::Titlebar;
	}

	GraphicsOptions::fullscreenModeOn = !GraphicsOptions::fullscreenModeOn;
}