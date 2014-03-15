#include "Game.h"

Game::Game () {
		//all we need to play
	gameWindow = new RenderWindow (VideoMode (1200, 700), "ZPR Survival");
	keyboard = new KeyboardInterface ();	
	mouse = new MouseInterface ();
	player = new Player ();
	state = INIT;
	TIME_PER_FRAME = seconds (1.f / 60.f);		//static frame (60 fps)
	
	generator = new MapGenerator(2048, 2048);		//#TEMP
	mapTexture.loadFromImage(generator->GetMap());  
	mapSprite.setTexture(mapTexture);
	mapSprite.setPosition (-1024+600, -1024+350);			
													//.....

	font.loadFromFile ("misc/segoeuil.ttf");	
}

Game::~Game () {
	delete gameWindow;
	delete player;
	delete keyboard;
	delete mouse;
	delete generator;
}

void Game::initialize () {
		//INIT
	gameWindow->setPosition (Vector2<int> (0, 0));		//push the gameWindow to the left-top corner
	this->state = IN_MENU;
		
		//IN_MENU
		//empty (for now)

		//PLAYING
		//#TEMP later these calls will be in other methods

	player->setPlayer ();	//prepares player for the game
		//set player position to the center of the screen
	player->playerController.setPlayerPosition (Vector2<int> (gameWindow->getSize ().x / 2, gameWindow->getSize ().y / 2));
}

void Game::run () {
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	timeSinceLastUpdate += clock.restart ();

	while (gameWindow->isOpen ()) {
		processEvents ();
		timeSinceLastUpdate += clock.restart ();			//this whole idea is to prevent...

		while (timeSinceLastUpdate > TIME_PER_FRAME) {
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents ();

			if (state == EXIT)
				gameWindow->close ();

			update (TIME_PER_FRAME);						//...game from occasional lags
		}
		render ();
	}
}

void Game::terminate () {

}

void Game::processEvents () {
		//handle mouse position and imput
	mouse->capturePosition (*gameWindow, player);

		//handle keyboard input
	Event event;
	int newState = -1;
	while (gameWindow->pollEvent (event)) {
		switch (event.type) {
			case Event::KeyPressed:			//inputHandle() returns proper new state
				newState = keyboard->inputHandle (event.key.code, true, state, player);
				break;
			case Event::KeyReleased:
				newState = keyboard->inputHandle (event.key.code, false, state, player);
				break;
			case Event::Closed:
				gameWindow->close ();
				break;
			default:
				break;
		}
	}

	switch (newState) {
		case UNKNOWN: state = UNKNOWN; break;
		case INIT: state = INIT; break;
		case IN_MENU: state = IN_MENU; break;
		case PLAYING: state = PLAYING; break;
		case PAUSE: state = PAUSE; break;
		case EXIT: state = EXIT; break;
		default:
			break;
	}
}

void Game::update (Time deltaTime) {
	player->playerController.setDeltaTime (deltaTime);
	player->update ();
		
		//set the world displacement vector relatively to player
	globalDisplacement = player->playerController.getDisplacement ();
	mapSprite.move (-globalDisplacement);
				 // ^ mind the sign!
}

void Game::render () {
	gameWindow->clear ();
	this->draw();
	
	//#TEMP test
	stringstream ss;
	ss << player->playerController.getFSpeed ();
	std::string result(ss.str ());
	Text text (result, font);
	text.setCharacterSize (30);
	text.setColor (Color::White);
	text.setPosition (10, 5);
	gameWindow->draw (text);

	ss.str ("");
	ss << player->playerController.getRSpeed ();
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 30);
	gameWindow->draw (text);

	ss.str ("");
	ss << player->playerController.getMousePosition ().x;
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 55);
	gameWindow->draw (text);

	ss.str ("");
	ss << player->playerController.getMousePosition().y;
	result = ss.str ();
	text.setString (result);
	text.setPosition (10, 80);
	gameWindow->draw (text);
	//=================================

	gameWindow->display ();
}

void Game::draw () {
	gameWindow->draw(mapSprite);
	gameWindow->draw (*player);
}

