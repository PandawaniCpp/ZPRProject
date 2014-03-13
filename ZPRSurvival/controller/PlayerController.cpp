#include "PlayerController.h"


PlayerController::PlayerController () {
	forSpeed = 0;
	revSpeed = 0;
	maxFSpeed = 300;
	maxRSpeed = 150;
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
