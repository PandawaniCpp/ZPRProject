/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Game.h"

std::string Game::TITLE = "#TITLE";

Game::Game () {
	// All we need to play.
	gameWindow = new RenderWindow (GraphicsOptions::testVideoMode, Game::TITLE, GraphicsOptions::videoStyle);	// Create new Window
	playerController = new PlayerController ();
	itemController = new ItemController ();
	console = new Console ();
	worldMap = new WorldMapView(0.0, 0.3, 8000, 3, 20000, 20000);
	//worldMap->getMapImage().saveToFile("./perlinMapstopro.png");

	// sf::View init.
	worldView = gameWindow->getDefaultView ();
	gameWindow->setView (worldView);
	
	state = Game::State::INIT;		// Proper first state

	console->insert ("object body x", worldView.getCenter ().x / GraphicsOptions::pixelPerMeter);
	console->insert ("object body y", worldView.getCenter ().y / GraphicsOptions::pixelPerMeter);
}

Game::~Game () {
	delete gameWindow;
	
	// Scene graph's destructor deallocates all graph's objects (all views).
}

void Game::initialize () {
	gameWindow->setKeyRepeatEnabled (false);			// Prevents from unintended key repetition
	
	// Set fonts
	fontHolder.load (Fonts::F_MENU, "resources/segoeuil.ttf");
	fontHolder.load (Fonts::F_CONSOLE, "resources/droidmono.ttf");
	// World information 
	worldBounds.top = worldBounds.left = 0.f;	// Top left corner (0, 0)
	worldBounds.height = 10000;					// World size
	worldBounds.width = 10000;					// #TODO put proper numbers from WorldMap
	worldView.setCenter (worldMap->getSpawnPoint());

	// Initialize main layers.
	layersInit ();

	// Set default parameters of objects owned.
	objectsInit ();

	// Set default game options.
	applyOptions ();

	// If everything's fine, move on to the next state.
	this->state = Game::State::IN_MENU;
}

void Game::run () {
	// Calculates time difference between frames and corrects occasional lags (if occured).
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	timeSinceLastUpdate += clock.restart ();
	PlayerController::deltaTime = timePerFrame;

	// Main game loop (handle events -> update everything -> render eveything)
	while (gameWindow->isOpen ()) {
		processEvents ();
		timeSinceLastUpdate += clock.restart ();			// This whole idea is to protect...

		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			processEvents ();

			if (state == Game::State::EXIT)
				gameWindow->close ();

			update ();										//...game from lags' consequences. 
		}
		render ();
	}
}

void Game::terminate () {

}

PlayerController * Game::getPlayerController () {
	return playerController;
}

void Game::layersInit () {
	// Initialize game scene graph
	for (std::size_t i = 0; i < LAYER_COUNT; ++i) {
		GameObject::Ptr layer (new GameObject ());
		sceneLayers[i] = layer.get ();
		sceneGraph.attachChild (layer);
	}

	// Attach map, console and player to game layers
	attachChild (worldMap, Game::MAP);
	attachChild (console, Game::CONSOLE);
	attachChild ((Animated<Textures::PLAYER>*)playerController->getEntity(0)->get(), Game::PLAYER);

	/*// Attach console object to console layer
	GameObject::Ptr consoleLayer (console);
	sceneLayers[Game::CONSOLE]->attachChild(consoleLayer);

	// Attach player view to player layer
	GameObject::Ptr playerLayer; 
	playerLayer.swap(static_cast<GameObject::Ptr>(playerController->getEntity (0)));
	sceneLayers[Game::PLAYER]->attachChild (playerLayer);*/
}

void Game::objectsInit () {
	// Prepares player for the game.
	//playerController->setPlayer ();	

	// Set player position to the spawn point defined in World Map.
	//playerController->getPlayer ()->setPosition (worldMap->getSpawnPoint());

	// Set default console's parameters
	console->insert ("x", 0);
	console->insert ("y", 0);
	console->insert ("dx", 0);
	console->insert ("dy", 0);
	console->insert ("direction", 0);
	console->insert ("rotation", 0);
	console->insert ("current resolution", GraphicsOptions::getCurrentResolution ());
	console->insert ("b2Body counter", 0);
	//console->insert ("player body x", playerController->getPlayerView ()->getPosition ().x / GraphicsOptions::pixelPerMeter);
	//console->insert ("player body y", playerController->getPlayerView ()->getPosition ().y / GraphicsOptions::pixelPerMeter);
	console->insert ("avail. resolutions", GraphicsOptions::getResolutionsAvailable ());
	console->setFont (fontHolder.get (Fonts::F_CONSOLE));

	// Items init.		#TEMP !!!!!
	/*std::vector<std::vector<std::vector<sf::Vector2f> > >positions = worldMap->getPoisson()->getPositions();
	for (auto & pos1 : positions) {
		for (auto & pos2 : pos1) {
			for (auto & pos : pos2) {
				//ItemView * item = new ItemView (itemTextureHolder.get (Textures::I_STONE));
				//item->setPosition (pos.x, pos.y);
				//item->setScale (0.5f, 0.5f);
				SurvivalObjectView::Ptr itemEntity;
				sf::Vector2f position(pos.x, pos.y);
				ItemView * item = itemController->createItem(Textures::I_STONE, position);
				if (item != nullptr)
					itemEntity.reset(item);
				sceneLayers[Game::ITEMS]->attachChild(itemEntity);
			}
		}
	}*/
}

void Game::applyOptions () {
	timePerFrame = seconds (1.f / GraphicsOptions::fps);			// Static frame, (1 / x) = x fps.
	GraphicsOptions::vSyncOn ? gameWindow->setVerticalSyncEnabled (true) : gameWindow->setVerticalSyncEnabled (false);

	if (state != Game::INIT)
		gameWindow->create (GraphicsOptions::videoMode, Game::TITLE, GraphicsOptions::videoStyle);
	console->update ("current resolution", GraphicsOptions::getCurrentResolution());

	// Update sf::View
	worldView = gameWindow->getDefaultView ();
	worldView.setCenter(5000,5000);
	gameWindow->setView (worldView);
}

void Game::processEvents () {
	// Handle mouse position and clicks.
	mouseInput ();

	// Handle keyboard input.
	Event event;
	
	while (gameWindow->pollEvent (event)) {
		switch (event.type) {
			case Event::KeyPressed:			// Pass it forward to keyboardInput().
				keyboardInput (event);
				break;
			case Event::KeyReleased:
				keyboardInput (event);
				break;
			case Event::Closed:
				gameWindow->close ();
				break;
			default:
				break;
		}
	}
}

void Game::keyboardInput (const Event event) {
	// #TODO
	//		PASS SPECIFIC KEY FUNCTIONALITY TO KEYBOARD INTERFACE
	// #TODO

	// Special keys prepared for later interpretation.
	unsigned keyFlags = event.key.control * 1 | event.key.shift * 2 | event.key.alt * 4 | event.key.system * 8;

	// #TODO Check if these conditions can be written with 'else-if'
	if (event.key.code == Keyboard::Escape)		//exit the game
		state = Game::EXIT;						//#TEMP

	if (event.key.code == Keyboard::F1 && Keyboard::isKeyPressed (event.key.code)) 
		Console::visible = !Console::visible;

	// Toggles fullscreen on/off
	if (Console::visible && keyFlags & KeyboardInterface::CONTROL &&  event.key.code == Keyboard::F && Keyboard::isKeyPressed (event.key.code)) {
		if (GraphicsOptions::fullscreenModeOn)
			setFullscreenEnabled (false);
		else
			setFullscreenEnabled (true);
	}

	if (Console::visible && keyFlags & KeyboardInterface::CONTROL && event.key.code == Keyboard::Add && Keyboard::isKeyPressed (event.key.code)) {
		GraphicsOptions::switchResolution (true);
		applyOptions ();
	}

	if (Console::visible && keyFlags & KeyboardInterface::CONTROL && event.key.code == Keyboard::Subtract && Keyboard::isKeyPressed (event.key.code)) {
		GraphicsOptions::switchResolution (false);
		applyOptions ();
	}

	switch (state) {							//controls the game state
		case Game::State::IN_MENU:
			if (event.key.code == Keyboard::Return)		//#TEMP
				state = Game::PLAYING;				//pseudo-start of the game
			break;
		case Game::State::PLAYING: 						//all events in the actual game
			//playerController->preparePlayerMove (event.key.code, Keyboard::isKeyPressed (event.key.code));
			state = Game::PLAYING;
		default:
			break;
	}
}

void Game::mouseInput () {
	mousePosition = static_cast<Vector2f>(Mouse::getPosition (*gameWindow)) + 
		worldView.getCenter() -
		worldView.getSize() / 2.0f;
}

void Game::update () {
	worldMap->t += rand()%750/100000.0;

	Player::boxWorld.Step (1.0 / GraphicsOptions::fps, 8, 3);
	/*for (b2Body* BodyIterator = Player::boxWorld.GetBodyList (); BodyIterator != 0; BodyIterator = BodyIterator->GetNext ()) {
		BodyIterator->SetLinearVelocity (b2Vec2 (1, 1));
	}*/

	console->update ("b2Body counter", Player::boxWorld.GetBodyCount());

	// Check if some keys are released (sometimes release event is not triggered somehow...).
	/*int direction = player->getDirection ();
	if (direction != 0) {
		if (!Keyboard::isKeyPressed (Keyboard::W) && direction & Player::UP)
			playerController->preparePlayerMove (Keyboard::W, false);
		if (!Keyboard::isKeyPressed (Keyboard::S) && direction & Player::DOWN)
			playerController->preparePlayerMove (Keyboard::S, false);
		if (!Keyboard::isKeyPressed (Keyboard::A) && direction & Player::LEFT)
			playerController->preparePlayerMove (Keyboard::A, false);
		if (!Keyboard::isKeyPressed (Keyboard::D) && direction & Player::RIGHT)
			playerController->preparePlayerMove (Keyboard::D, false);
	}*/
	
	// Update player accordingly to mouse position change.
	playerController->updateEntities ();	

	// Update console ouput.
	/*console->update ("x", player->getPosition ().x);
	console->update ("y", player->getPosition ().y);
	console->update ("dx", player->getDisplacement ().x);
	console->update ("dy", player->getDisplacement ().y);
	console->update ("direction", (float)player->getDirection ());
	console->update ("rotation", player->getRotation ());
	console->update ("player body x", playerController->getPlayerView ()->getPosition ().x / GraphicsOptions::pixelPerMeter);
	console->update ("player body y", playerController->getPlayerView ()->getPosition ().y / GraphicsOptions::pixelPerMeter);*/


	// Move player
	/*Vector2f position = player->getPosition ();
	playerController->move (position, player->getDisplacement ());
	player->setPosition (position);

	// Set the world displacement vector relatively to player.
	worldView.setCenter (player->getPosition() + player->getOffset ());
	gameWindow->setView (worldView);*/

	// Vector for displacement correction.
	sf::Vector2f vec (worldView.getCenter () - worldView.getSize () / 2.0f);

	// Correct console displacement (always in top-left corner).
	console->setPosition (vec);

	// Correct map displacement.
	worldMap->setPosition (vec);
	vec.y -= worldMap->getWorldBounds().y - GraphicsOptions::videoMode.height;		// !!!!!
	worldMap->setViewPosition (vec);	
	worldMap->update();
}

void Game::render () {
	gameWindow->clear ();		// Clear eveything.
	draw ();
	gameWindow->display ();
}

void Game::draw () {
	//playerController->prepareView ();

	// Draw all layers in order.
	sceneGraph.drawAll (gameWindow);
}

void Game::attachChild (GameObject * object, Game::Layer layer) {
	GameObject::Ptr ptrLayer (object);
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