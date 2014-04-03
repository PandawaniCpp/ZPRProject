/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#include "Game.h"

Game::Game () {
	// All we need to play.
	gameWindow = new RenderWindow (VideoMode (1200, 700), "ZPR Survival");
	playerController = new PlayerController ();
	generator = new MapGenerator (100, 100, 100);		//#TEMP
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
	font.loadFromFile ("resources/segoeuil.ttf");		// #TODO use different font

	//mapTexture.loadFromImage(generator->GetMap());	// #TEMP
	//mapSprite.setTexture(mapTexture);
	//mapSprite.setPosition (-1024+600, -1024+350);			
	generator->GetMap ().saveToFile ("Map.png");		//....

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
		sceneGraph.attachChild (std::move (layer));
	}
	
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

	// Main game loop (handle events -> update everything -> render eveything)
	while (gameWindow->isOpen ()) {
		processEvents ();
		timeSinceLastUpdate += clock.restart ();			// This whole idea is to protect...

		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			processEvents ();

			if (state == Game::State::EXIT)
				gameWindow->close ();

			update (timePerFrame);							//...game from lags' consequences. 
		}
		render ();
	}
}

void Game::terminate () {

}

PlayerController * Game::getPlayerController () {
	return playerController;
}

void Game::processEvents () {
	// Handle mouse position and clicks.
	mouseInput ();

	// Handle keyboard input.
	Event event;
	int newState = -1;
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

	/*switch (state) {
		case Game::State::UNKNOWN: state = Game::State::UNKNOWN; break;
		case Game::State::INIT: state = Game::State::INIT; break;
		case Game::State::IN_MENU: state = Game::State::IN_MENU; break;
		case Game::State::PLAYING: state = Game::State::PLAYING; break;
		case Game::State::PAUSE: state = Game::State::PAUSE; break;
		case Game::State::EXIT: state = Game::State::EXIT; break;
		default:
			break;
	}*/
}

void Game::keyboardInput (sf::Keyboard::Key key) {
	if (key == Keyboard::Escape)		//exit the game
		state = Game::EXIT;					//#TEMP

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

void Game::update (Time deltaTime) {
	playerController->setDeltaTime (deltaTime);		// Update time difference between frames.
	playerController->update (mousePosition);	//update player according to mouse position change.

	// Set the world displacement vector relatively to player.
	//	#TODO Change the world movement using sf::View
	globalDisplacement = playerController->getPlayer ()->getDisplacement ();
	generator->move (-globalDisplacement);
}

void Game::render () {
	gameWindow->clear ();		// Clear eveything.
	this->draw ();

	//#TEMP test
	stringstream ss;
	ss << playerController->getPlayer ()->getDisplacement ().x;
	std::string result (ss.str ());
	Text text (result, font);
	text.setCharacterSize (30);
	text.setColor (Color::White);
	text.setPosition (10, 5);
	gameWindow->draw (text);

	ss.str ("");
	ss << playerController->getPlayer ()->getDisplacement ().y;
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 30);
	gameWindow->draw (text);

	ss.str ("");
	ss << generator->getPosition ().x;
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 55);
	gameWindow->draw (text);

	ss.str ("");
	ss << generator->getPosition ().y;
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 80);
	gameWindow->draw (text);

	ss.str ("");
	ss << playerController->getPlayer ()->getDirection ();
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 105);
	gameWindow->draw (text);
	//=================================

	gameWindow->display ();
}

void Game::draw () {
	//gameWindow->draw(mapSprite);
	playerController->prepareView ();
	generator->draw (gameWindow);
	playerController->getPlayerView ()->draw (*gameWindow);
}

