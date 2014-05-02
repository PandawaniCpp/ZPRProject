/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Player.h"

Player::Player () {
	// Current animation parameters
	frameNumber = 0;
	frameDuration = sf::seconds (0.5f);
	currentAnimation = Textures::P_IDLE;
	animationRepeat = true;

	this->setOrigin (frameData[currentAnimation].x / 2.0, frameData[currentAnimation].y / 2.0);
}

Player::Player (GameObject::Prefab prefab) {
	// Current animation parameters
	frameNumber = 0;
	frameDuration = sf::seconds (0.5f);
	currentAnimation = Textures::P_IDLE;
	animationRepeat = true;

	this->setOrigin (prefab.width * prefab.originX, prefab.height * prefab.originY);
}

Player::~Player () {
}

void Player::draw (sf::RenderWindow& window) const {
	window.draw (*this);
}

/*void Player::changeTexture () {
	this->Dynamic::setTexture (textureHolder.get (currentAnimation));
}*/
