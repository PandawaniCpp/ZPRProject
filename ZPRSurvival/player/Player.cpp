#include "Player.h"

Player::Player (){
	displacement.x = 0;
	displacement.y = 0;
	size.x = 50;
	size.y = 50;
	maxFSpeed = 400;
	maxRSpeed = 250;
	forSpeed = 0;		
	revSpeed = 0;
	rotation = 0;
	direction = 0;
	phase = STOP;
}

Player::~Player () {
}

PlayerState Player::getState () {
	return playerState;
}

void Player::setState (PlayerState playerState) {
	this->playerState = playerState;
}
