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
