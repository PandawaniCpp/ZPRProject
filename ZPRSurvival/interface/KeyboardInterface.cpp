#include "KeyboardInterface.h"

KeyboardInterface::KeyboardInterface () {
}

KeyboardInterface::~KeyboardInterface () {
}

int KeyboardInterface::inputHandle (sf::Keyboard::Key key, bool isPressed, int state, Player * player) {
	if (key == sf::Keyboard::Escape)		//exit the game
		return EXIT;						//#TEMP

	switch (state) {						//controls the game state
		case IN_MENU: 
			if (key == sf::Keyboard::Return)		//#TEMP
				return PLAYING;						//pseudo-start of the game
			break;
		case PLAYING: {						//all events in the actual game
			int movingState = 0;					//how the player move...
			if (key == sf::Keyboard::W)
				movingState = movingState | UP;
			else if (key == sf::Keyboard::S)
				movingState = movingState | DOWN;
			else if (key == sf::Keyboard::A)
				movingState = movingState | LEFT;
			else if (key == sf::Keyboard::D)
				movingState = movingState | RIGHT;	//...
			player->playerController.preparePlayerMove (movingState, isPressed);
			return PLAYING;
		}
		default: 
			return -1;
	}
	return -1;
}