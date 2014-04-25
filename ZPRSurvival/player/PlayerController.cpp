/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "PlayerController.h"

PlayerController::PlayerController () {
	player = new Player;
	playerView = new PlayerView;
}

PlayerController::~PlayerController () {
}

void PlayerController::update (Vector2i mousePosition) {
	// #TODO insert texture update

	// Rotation update.
	calculatePlayerRotation (mousePosition);

	// Displacement update.
	if ((player->getSpeed() != 0) || (player->getDirection() != 0))
		calculatePlayerMove ();

	// Position update.
	Vector2<float> position = player->getPosition ();
	playerView->setPosition (position.x, position.y);
}

void PlayerController::prepareView () {
	playerView->setRotation (player->getRotation());
	playerView->setPosition (player->getPosition());
}


void PlayerController::preparePlayerMove (Keyboard::Key key, bool isPressed) {
	int direction = player->getDirection ();
	int directionChange = 0;					
	
	if (key == sf::Keyboard::W)						// Player keys for moving.
		directionChange = AnimatedObject::UP;		// #TODO Use key bindings (changed in options)
	else if (key == sf::Keyboard::S)
		directionChange = AnimatedObject::DOWN;
	else if (key == sf::Keyboard::A)
		directionChange = AnimatedObject::LEFT;
	else if (key == sf::Keyboard::D)
		directionChange = AnimatedObject::RIGHT;	//...

	if (isPressed)		// Add or remove new directions.
		direction = direction | directionChange;
	else
		direction = direction ^ directionChange;

	player->setDirection (direction);
}

void PlayerController::calculatePlayerMove () {
	calculateMove (player);
}

void PlayerController::setPosition (Vector2<float> position) {
	player->setPosition (position);
}

void PlayerController::calculatePlayerRotation (Vector2i mousePosition) {
	// Difference between mouse and player position.
	float deltaX = mousePosition.x - player->getPosition ().x;
	float deltaY = mousePosition.y - player->getPosition ().y;
	Vector2<float> rotationVector (deltaX, deltaY);
	float rotation = 0;

	calculateRotation (rotation, rotationVector);

	player->setRotation (rotation);
}

void PlayerController::setPlayer () {
	// Rotate relatively to the player's center.
	playerView->setOrigin (player->getSize ().x / 2, player->getSize ().y / 2);	
}

Player * PlayerController::getPlayer () {
	return player;
}

PlayerView * PlayerController::getPlayerView () {
	return playerView;
}