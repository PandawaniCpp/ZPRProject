/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#include "MouseInterface.h"

MouseInterface::MouseInterface () {
}

MouseInterface::~MouseInterface () {
}

void MouseInterface::capturePosition (RenderWindow & window) {
	mousePosition = Mouse::getPosition (window);
}

Vector2i MouseInterface::getPosition () {
	return mousePosition;
}
