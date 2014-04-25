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
	//generator = new MapGenerator (100, 100, 100);		//#TEMP
	worldView = gameWindow->getDefaultView ();
	
	state = Game::State::INIT;		// Proper first state
}

Game::~Game () {
	delete gameWindow;
	delete playerController;
	//delete worldMap;		#TODO ERROR! CHECK THIS
	//delete console;		#TODO ERROR! CHECK THIS
	// #TODO Delete the rest of the objects
}

void Game::initialize () {
	gameWindow->setKeyRepeatEnabled (false);			// Prevents from unintended key repetition
	//gameWindow->setPosition (Vector2<int> (0, 0));			// Push the gameWindow to the left-top corner
	
	// Set fonts
	fontHolder.load (Fonts::F_MENU, "resources/segoeuil.ttf");
	fontHolder.load (Fonts::F_CONSOLE, "resources/droidmono.ttf");

	//mapTexture.loadFromImage(generator->GetMap());	// #TEMP
	//mapSprite.setTexture(mapTexture);
	//mapSprite.setPosition (-1024+600, -1024+350);			
	//generator->GetMap ().saveToFile ("Map.png");		//....

	// World information 
	// #TODO put in different function
	worldBounds.top = worldBounds.left = 0.f;	// Top left corner (0, 0)
	worldBounds.height = 5000;					// World size
	worldBounds.width = 5000;					// #TODO put proper numbers
	worldView.setCenter (worldView.getSize ().x / 2.f, worldView.getSize ().y / 2.f);
	scrollSpeed = playerController->getPlayer ()->getSpeed ();	// Scrolling speed is the player's moving speed.

	// Initialize game scene graph
	for (std::size_t i = 0; i < LAYER_COUNT; ++i) {
		SurvivalObjectView::Ptr layer (new SurvivalObjectView ());
		sceneLayers[i] = layer.get ();
		sceneGraph.attachChild (layer);
	}

	// Initialize main layers.
	layersInit ();

	// Set default parameters of objects owned.
	objectsInit ();

	// Set default game options.
	applyOptions ();
	
	// #TODO put this in other function (this is just initialization)
	playerController->setPlayer ();	// Prepares player for the game.
	// Set player position to the center of the screen.
	playerController->getPlayer()->setPosition (Vector2<float> ((float)gameWindow->getSize ().x / 2, (float)gameWindow->getSize ().y / 2));
	//.................................

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
	// Attach console object to console layer
	SurvivalObjectView::Ptr consoleLayer (console);
	SurvivalObjectView::Ptr mapLayer(worldMap);
	sceneLayers[Game::MAP]->attachChild(mapLayer);
	sceneLayers[Game::CONSOLE]->attachChild(consoleLayer);

	// Attach player view to player layer
	SurvivalObjectView::Ptr playerLayer (playerController->getPlayerView());
	sceneLayers[Game::PLAYER]->attachChild (playerLayer);
}

void Game::objectsInit () {
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
	// #TEMP
	timePerFrame = seconds (1.f / 100.f);			// Static frame, (1 / x) = x fps.

	GraphicsOptions::vSyncOn ? gameWindow->setVerticalSyncEnabled (true) : gameWindow->setVerticalSyncEnabled (false);
	gameWindow->create (GraphicsOptions::videoMode, Game::TITLE, GraphicsOptions::videoStyle);
	console->update ("current resolution", GraphicsOptions::getCurrentResolution());
	sf::Style::Fullscreen;
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
	mousePosition = Mouse::getPosition (*gameWindow);
}

void Game::update () {
	playerController->update (mousePosition);	//update player according to mouse position change.

	// Update console ouput.
	console->update ("x", playerController->getPlayer ()->getPosition ().x);
	console->update ("y", playerController->getPlayer ()->getPosition ().y);
	console->update ("dx", playerController->getPlayer ()->getDisplacement ().x);
	console->update ("dy", playerController->getPlayer ()->getDisplacement ().y);
	console->update ("direction", (float)playerController->getPlayer ()->getDirection ());
	console->update ("rotation", playerController->getPlayer ()->getRotation ());

	// Set the world displacement vector relatively to player.
	//	#TODO Change the world movement using sf::View
	globalDisplacement = playerController->getPlayer ()->getDisplacement ();
	//generator->move (-globalDisplacement);
}

void Game::render () {
	gameWindow->clear ();		// Clear eveything.
	draw ();
	gameWindow->display ();
}

void Game::draw () {
	//gameWindow->draw(mapSprite);
	playerController->prepareView ();
	//generator->draw (gameWindow);

	// Draw all layers in order.
	sceneGraph.drawAll (*gameWindow);
	
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