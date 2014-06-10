/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "PlayerModel.h"

PlayerModel::PlayerModel (){
	/*displacement.x = 0;
	displacement.y = 0;
	size.x = 50;
	size.y = 50;
	speed = 2000;
	rotation = 0;
	direction = 0;*/
}

PlayerModel::~PlayerModel () {
}

PlayerModel::State PlayerModel::getState () {
	return state;
}

sf::Vector2<float> PlayerModel::getOffset () {
	return offset;
}

void PlayerModel::setState (PlayerModel::State state) {
	this->state = state;
}

void PlayerModel::setOffset (sf::Vector2<float> offset) {
	this->offset = offset;
}
