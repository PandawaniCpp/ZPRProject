#include "Game.h"

Game::Game () {
	gameWindow = new sf::RenderWindow (sf::VideoMode (1200, 700), "ZPR Survival");
	keyboard = new KeyboardInterface ();
	player = new Player ();
	state = INIT;
}


Game::~Game () {
	delete gameWindow;
	delete player;
}

void Game::initialize () {
	player->setPlayer ();
	this->state = IN_MENU;
}

void Game::run () {
	while (gameWindow->isOpen ()) {
		processEvents ();
		update ();
		render ();
	}
}

void Game::terminate () {

}

void Game::processEvents () {
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
		case 0: state = UNKNOWN; break;
		case 1: state = INIT; break;
		case 2: state = IN_MENU; break;
		case 3: state = PLAYING; break;
		case 4: state = PAUSE; break;
		default:
			break;
	}
}

void Game::render () {
	gameWindow->clear ();
	this->draw();
	gameWindow->display ();
}

void Game::update () {
	player->update ();
}

void Game::draw () {
	gameWindow->draw (*player);
}

