#include "PlayerController.h"

PlayerController::PlayerController () {
	forSpeed = 0;
	revSpeed = 0;
	maxFSpeed = 400;
	maxRSpeed = 250;
	size.x = 50;
	size.y = 50;
}

PlayerController::~PlayerController () {
}

void PlayerController::setPlayerPosition (Vector2<double> position) {
	this->position.x = position.x;
	this->position.y = position.y;
}

void PlayerController::setMousePosition (sf::Vector2i position) {
	mousePosition = position;
}

void PlayerController::calculateRotation () {
	float deltaX = mousePosition.x - (position.x);
	float deltaY = mousePosition.y - (position.y);

		//calc. vector rotation. 0 degrees == "up", clockwise.
	if (deltaX > 0) {
		if (deltaY < 0) {					//(0; 90) degrees
			rotation = atan (deltaX / -deltaY) * 180 / PI;
			return;
		}
		else {								//(90; 180) degrees
			rotation = atan (deltaY / deltaX) * 180 / PI + 90;
			return;
		}
	}
	else if (deltaX < 0) {
		if (deltaY > 0) {					//(180; 270) degrees
			rotation = atan (-deltaX / deltaY) * 180 / PI + 180;
			return;
		}
		else {								//(270; 360) degrees
			rotation = atan (-deltaY / -deltaX) * 180 / PI + 270;
			return;
		}
	}

    if (deltaX == 0) {			//check if 'zeros'
		if (deltaY <= 0)
			rotation = 0;		//UP, 0 deg.
		else
			rotation = 180;		//DOWN, 180 deg.
		return;
	}

	if (deltaY == 0) {			//check if 'zeros'
		if (deltaX < 0)
			rotation = 270;		//LEFT, 270 deg.
		else
			rotation = 90;		//RIGHT, 90 deg.
		return;
	}
}

/**************** getters ****************/
playerState PlayerController::getState () {
	return state;
}

Vector2<float> PlayerController::getSize () {
	return size;
}

sf::Vector2i PlayerController::getMousePosition () {
	return mousePosition;
}
