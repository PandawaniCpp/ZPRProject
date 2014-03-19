#include "Player.h"

Player::Player (){
	forSpeed = 0;		// #TODO set via setters
	revSpeed = 0;
	maxFSpeed = 200;
	maxRSpeed = 250;
	size.x = 50;
	size.y = 50; 
}

Player::~Player () {
}

PlayerState Player::getState () {
	return playerState;
}

void Player::setState (PlayerState playerState) {
	this->playerState = playerState;
}
