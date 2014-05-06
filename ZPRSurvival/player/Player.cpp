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
	frameDuration = sf::seconds (0.5f);
	currentAnimation = Textures::P_IDLE;
	animationRepeat = true;
	
	// Dynamic body parameters.
	rotationSpeed = 0.5f;
	acceleration = 10.f;
	runModifier = 2.f;
	anglePrecision = 10.f * DEG_TO_RAD;
	
	// Set ID
	entityId = Entities::PLAYER;

	this->setOrigin (frameData[currentAnimation].x / 2.0, frameData[currentAnimation].y / 2.0);
	this->resetAnimation ();
}

Player::Player (GameObject::Prefab * prefab) {
	// Current animation parameters
	frameDuration = sf::seconds (0.5f);
	currentAnimation = prefab->texture.playerTexture;
	animationRepeat = true;

	// Dynamic body parameters.
	rotationSpeed = prefab->rotationSpeed;
	acceleration = prefab->acceleration;
	runModifier = prefab->runModifier;
	anglePrecision = rotationSpeed / 2.0 * DEG_TO_RAD;

	// Set ID
	entityId = Entities::PLAYER;	// #TODO NAPRAW !!!!!

	this->setOrigin (prefab->width * prefab->originX, prefab->height * prefab->originY);
	this->resetAnimation ();
}

Player::~Player () {
}

void Player::draw (sf::RenderWindow * window) const {
	window->draw (*this);
}