/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

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
