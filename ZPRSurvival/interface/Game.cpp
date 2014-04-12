/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Game.h"

Game::Game () {
	// All we need to play.
	gameWindow = new RenderWindow (VideoMode (1200, 700), "ZPR Survival");
	playerController = new PlayerController ();
	console = new Console ();
	//generator = new MapGenerator (100, 100, 100);		//#TEMP
	worldView = gameWindow->getDefaultView ();
	
	state = Game::State::INIT;		// Proper first state
}

Game::~Game () {
	delete gameWindow;
	delete playerController;
	delete generator;
	// #TODO Delete the rest of the objects
}

void Game::initialize () {
	timePerFrame = seconds (1.f / 100.f);			// Static frame, (1 / x) = x fps.
	gameWindow->setKeyRepeatEnabled (false);			// Prevents from unintended key repetition
	gameWindow->setPosition (Vector2<int> (0, 0));			// Push the gameWindow to the left-top corner
	
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
	sceneLayers[Game::CONSOLE]->attachChild (consoleLayer);

	// Attach player view to player layer
	SurvivalObjectView::Ptr playerLayer (playerController->getPlayerView());
	sceneLayers[Game::PLAYER]->attachChild (playerLayer);
}

void Game::objectsInit () {
	// Set default console's parameters
	console->insert ("x: ", 0);
	console->insert ("y: ", 0);
	console->insert ("dx: ", 0);
	console->insert ("dy: ", 0);
	console->insert ("direction: ", 0);
	console->insert ("rotation: ", 0);
	console->setFont (fontHolder.get (Fonts::F_CONSOLE));
}

void Game::processEvents () {
	// Handle mouse position and clicks.
	mouseInput ();

	// Handle keyboard input.
	Event event;
	
	while (gameWindow->pollEvent (event)) {
		switch (event.type) {
			case Event::KeyPressed:			// Pass it forward to keyboardInput().
				keyboardInput (event.key.code);
				break;
			case Event::KeyReleased:
				keyboardInput (event.key.code);
				break;
			case Event::Closed:
				gameWindow->close ();
				break;
			default:
				break;
		}
	}
}

void Game::keyboardInput (sf::Keyboard::Key key) {
	if (key == Keyboard::Escape)		//exit the game
		state = Game::EXIT;					//#TEMP

	if (key == Keyboard::F1 && Keyboard::isKeyPressed (key))
		Console::visible = !Console::visible;

	switch (state) {							//controls the game state
		case Game::State::IN_MENU:
			if (key == Keyboard::Return)		//#TEMP
				state = Game::PLAYING;				//pseudo-start of the game
			break;
		case Game::State::PLAYING: 						//all events in the actual game
			playerController->preparePlayerMove (key, Keyboard::isKeyPressed (key));
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
	console->update ("x: ", playerController->getPlayer ()->getPosition ().x);
	console->update ("y: ", playerController->getPlayer ()->getPosition ().y);
	console->update ("dx: ", playerController->getPlayer ()->getDisplacement ().x);
	console->update ("dy: ", playerController->getPlayer ()->getDisplacement ().y);
	console->update ("direction: ", (float)playerController->getPlayer ()->getDirection ());
	console->update ("rotation: ", playerController->getPlayer ()->getRotation ());

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

