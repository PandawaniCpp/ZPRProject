#include "PlayerController.h"


PlayerController::PlayerController () {
	speed = 0.2;
}


PlayerController::~PlayerController () {
}

void PlayerController::setPlayerPosition (Vector2<double> position) {
	this->position.x = position.x;
	this->position.y = position.y;
}

playerState PlayerController::getState () {
	return state;
}
