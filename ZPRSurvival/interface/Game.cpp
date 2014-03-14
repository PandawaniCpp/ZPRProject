#include "Game.h"

Game::Game () {
	gameWindow = new sf::RenderWindow (sf::VideoMode (1200, 700), "ZPR Survival");
	keyboard = new KeyboardInterface ();
	mouse = new MouseInterface ();
	player = new Player ();
	state = INIT;
	TimePerFrame = sf::seconds (1.f / 60.f);
	
	/*generator = new MapGenerator(4096, 4096);
	mapTexture.loadFromImage(generator->GetMap()); 
	mapSprite.setTexture(mapTexture);*/

	font.loadFromFile ("misc/segoeuil.ttf");	
}

Game::~Game () {
	delete gameWindow;
	delete player;
}

void Game::initialize () {
	player->setPlayer ();
		//set position to the center of the screen
	player->playerController.setPlayerPosition (sf::Vector2<double> ((double)gameWindow->getSize ().x / 2, (double)gameWindow->getSize ().y / 2));
	this->state = IN_MENU;
}

void Game::run () {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	timeSinceLastUpdate += clock.restart ();
	while (gameWindow->isOpen ()) {
		processEvents ();
		timeSinceLastUpdate += clock.restart ();
		while (timeSinceLastUpdate > TimePerFrame) {
			timeSinceLastUpdate -= TimePerFrame;
			processEvents ();

			if (state == EXIT)
				gameWindow->close ();

			update (TimePerFrame);
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
	sf::Event event;
	int newState = -1;
	while (gameWindow->pollEvent (event)) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				newState = keyboard->inputHandle (event.key.code, true, state, player);
				break;
			case sf::Event::KeyReleased:
				newState = keyboard->inputHandle (event.key.code, false, state, player);
				break;
			case sf::Event::Closed:
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

void Game::update (sf::Time deltaTime) {
	player->playerController.setDeltaTime (deltaTime);
	player->update ();
}

void Game::render () {
	gameWindow->clear ();
	this->draw();
	
	//temporary test
	stringstream ss;
	ss << player->playerController.getFSpeed ();
	std::string result(ss.str ());
	sf::Text text (result, font);
	text.setCharacterSize (30);
	text.setColor (sf::Color::White);
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

