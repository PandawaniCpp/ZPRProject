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
	console = new Console ();
	worldMap = new WorldMapView();

	// sf::View init.
	worldView = gameWindow->getDefaultView ();
	gameWindow->setView (worldView);
	
	state = Game::State::INIT;		// Proper first state
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
	SurvivalObjectController::deltaTime = timePerFrame;

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
		SurvivalObjectView::Ptr layer (new SurvivalObjectView ());
		sceneLayers[i] = layer.get ();
		sceneGraph.attachChild (layer);
	}

	// Attach map view to map layer
	SurvivalObjectView::Ptr mapLayer (worldMap);
	sceneLayers[Game::MAP]->attachChild (mapLayer);

	// Attach console object to console layer
	SurvivalObjectView::Ptr consoleLayer (console);
	sceneLayers[Game::CONSOLE]->attachChild(consoleLayer);

	// Attach player view to player layer
	SurvivalObjectView::Ptr playerLayer (playerController->getPlayerView());
	sceneLayers[Game::PLAYER]->attachChild (playerLayer);
}

void Game::objectsInit () {
	// Prepares player for the game.
	playerController->setPlayer ();	

	// Set player position to the spawn point defined in World Map.
	playerController->getPlayer ()->setPosition (worldMap->getSpawnPoint ());

	// Set default console's parameters
	console->insert ("x", 0);
	console->insert ("y", 0);
	console->insert ("dx", 0);
	console->insert ("dy", 0);
	console->insert ("direction", 0);
	console->insert ("rotation", 0);
	console->insert ("current resolution", GraphicsOptions::getCurrentResolution ());
	console->insert ("avail. resolutions", GraphicsOptions::getResolutionsAvailable ());
	console->setFont (fontHolder.get (Fonts::F_CONSOLE));
}

void Game::applyOptions () {
	timePerFrame = seconds (1.f / GraphicsOptions::fps);			// Static frame, (1 / x) = x fps.
	GraphicsOptions::vSyncOn ? gameWindow->setVerticalSyncEnabled (true) : gameWindow->setVerticalSyncEnabled (false);
	gameWindow->create (GraphicsOptions::videoMode, Game::TITLE, GraphicsOptions::videoStyle);
	console->update ("current resolution", GraphicsOptions::getCurrentResolution());

	// Update sf::View
	worldView = gameWindow->getDefaultView ();
	worldView.setCenter(playerController->getPlayer ()->getPosition());
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
			playerController->preparePlayerMove (event.key.code, Keyboard::isKeyPressed (event.key.code));
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
	Player * player = playerController->getPlayer ();

	playerController->update (mousePosition);	//update player according to mouse position change.

	// Update console ouput.
	console->update ("x", playerController->getPlayer ()->getPosition ().x);
	console->update ("y", playerController->getPlayer ()->getPosition ().y);
	console->update ("dx", playerController->getPlayer ()->getDisplacement ().x);
	console->update ("dy", playerController->getPlayer ()->getDisplacement ().y);
	console->update ("direction", (float)playerController->getPlayer ()->getDirection ());
	console->update ("rotation", playerController->getPlayer ()->getRotation ());

	// Move player
	Vector2f position = player->getPosition ();
	playerController->move (position, player->getDisplacement ());
	player->setPosition (position);

	// Set the world displacement vector relatively to player.
	worldView.move (-playerController->getPlayer ()->getDisplacement ());
	gameWindow->setView (worldView);
}

void Game::render () {
	gameWindow->clear ();		// Clear eveything.
	draw ();
	gameWindow->display ();
}

void Game::draw () {
	playerController->prepareView ();

	// Draw all layers in order.
	sceneGraph.drawAll (gameWindow);
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