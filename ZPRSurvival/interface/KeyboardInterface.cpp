#include "KeyboardInterface.h"


KeyboardInterface::KeyboardInterface () {
}


KeyboardInterface::~KeyboardInterface () {
}

int KeyboardInterface::inputHandle (sf::Keyboard::Key key, bool isPressed, int state, Player * player) {
	switch (state) {
		case IN_MENU: 
			if (key == sf::Keyboard::Return)
				return PLAYING;
			break;
		case PLAYING: {
			int movingState = 0;
			if (key == sf::Keyboard::W)
				movingState = movingState | UP;
			else if (key == sf::Keyboard::S)
				movingState = movingState | DOWN;
			else if (key == sf::Keyboard::A)
				movingState = movingState | LEFT;
			else if (key == sf::Keyboard::D)
				movingState = movingState | RIGHT;
			player->playerController.prepareMove (movingState, isPressed);
			return PLAYING;
		}
		default: 
			return -1;
	}
	return -1;
}