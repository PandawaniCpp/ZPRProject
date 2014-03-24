#include "Player.h"

Player::Player (){
	displacement.x = 0;
	displacement.y = 0;
	size.x = 50;
	size.y = 50;
	speed = 400;
	rotation = 0;
	direction = 0;
}

Player::~Player () {
}

Player::State Player::getState () {
	return state;
}

void Player::setState (Player::State state) {
	this->state = state;
}
