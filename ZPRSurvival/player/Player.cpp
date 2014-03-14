#include "Player.h"

Player::Player (){
	texture.loadFromFile ("player.png");
}

Player::~Player () {
}

void Player::setPlayer () {
	setPlayerTexture ();
	setOrigin (playerController.getSize ().x / 2, playerController.getSize ().y / 2);
	update ();
}

void Player::update () {
		//insert texture update

		//rotation update
	playerController.calculateRotation ();
	this->setRotation ((float)playerController.getRotation ());
		//position update
	Vector2<double> position = playerController.getPosition ();
	this->setPosition ((float)position.x, (float)position.y);
	
	if ((playerController.getFSpeed() != 0) && (playerController.getRSpeed() != 0) || (playerController.getPhase() != STOP)) {
		playerController.calculateMove ();
		playerController.move ();
	}
}

void Player::setPlayerTexture () {
	this->setTexture (texture);
}
