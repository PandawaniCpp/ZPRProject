#include "Player.h"

Player::Player (){
	texture.loadFromFile ("player.png");
}

Player::~Player () {
}

void Player::setPlayer () {
	setPlayerTexture ();
	setOrigin (playerController.getSize ().x / 2, playerController.getSize ().y / 2);	//to rotate relatively to the player center
}

void Player::update () {
		//insert texture update

		//rotation update
	playerController.calculatePlayerRotation ();
	this->setRotation (playerController.getRotation ());
	
		//displacement update
	if ((playerController.getFSpeed() != 0) && (playerController.getRSpeed() != 0) || (playerController.getPhase() != STOP))
		playerController.calculateMove ();

		//position update
	Vector2<float> position = playerController.getPosition ();
	this->setPosition ((float)position.x, (float)position.y);
}

void Player::setPlayerTexture () {
	this->setTexture (texture);
}
