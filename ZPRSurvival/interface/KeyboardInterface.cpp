#include "KeyboardInterface.h"

KeyboardInterface::KeyboardInterface () {
}

KeyboardInterface::~KeyboardInterface () {
}

int KeyboardInterface::inputHandle (Keyboard::Key key, bool isPressed, int state, PlayerController * playerController) {
	if (key == Keyboard::Escape)		//exit the game
		return EXIT;						//#TEMP

	switch (state) {						//controls the game state
		case IN_MENU: 
			if (key == Keyboard::Return)		//#TEMP
				return PLAYING;						//pseudo-start of the game
			break;
		case PLAYING: {						//all events in the actual game
			playerController->preparePlayerMove (key, isPressed);
			return PLAYING;
		}
		default: 
			return -1;
	}
	return -1;
}