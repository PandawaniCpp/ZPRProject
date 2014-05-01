/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Player.h"

Player::Player () {
	// Set sizes for every animation of the player.
	Animated::frameData.insert (std::make_pair (Textures::P_IDLE, sf::Vector3<int> (50, 50, 10)));
	Animated::frameData.insert (std::make_pair (Textures::P_WALK, sf::Vector3<int> (50, 50, 10)));

	// Current animation parameters
	frameNumber = 0;
	frameDuration = sf::seconds (0.5f);
	currentAnimation = Textures::P_IDLE;
	animationRepeat = true;

	Animated::setPosition (5000, 5000);
	Animated::setOrigin (frameData[currentAnimation].x / 2, frameData[currentAnimation].y / 2);
}

Player::~Player () {
}

void Player::draw (sf::RenderWindow& window) const {
	GameObject * object = (Animated*) this;
	window.draw (*object);
}

/*void Player::changeTexture () {
	this->Animated::setTexture (textureHolder.get (currentAnimation));
}*/
