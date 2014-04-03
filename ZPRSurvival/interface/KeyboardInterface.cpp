/**
@author	Pawel Kaczynski
@date	03.04.2014

Part of the #TITLE survival game.
*/

#include "KeyboardInterface.h"
#include "Game.h"

KeyboardInterface::KeyboardInterface () {
}

KeyboardInterface::~KeyboardInterface () {
}

/*int KeyboardInterface::inputHandle (Keyboard::Key key, int state) {
	if (key == Keyboard::Escape)		//exit the game
		return Game::State::EXIT;			//#TEMP

	switch (state) {						//controls the game state
		case Game::State::IN_MENU:
			if (key == Keyboard::Return)		//#TEMP
				return Game::State::PLAYING;		//pseudo-start of the game
			break;
		case Game::State::PLAYING: {						//all events in the actual game
			game->getPlayerController()->preparePlayerMove (key, Keyboard::isKeyPressed (key));
			return Game::State::PLAYING;
		}
		default: 
			return -1;
	}
	return -1;
}*/