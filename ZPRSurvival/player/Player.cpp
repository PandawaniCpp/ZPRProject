#include "Player.h"


Player::Player (){
	texture.loadFromFile ("player.png");
}


Player::~Player () {
}

void Player::setPlayer () {
	setPlayerTexture ();
	playerController.setPlayerPosition (Vector2<double> (100, 100));
	update ();
}

void Player::update () {
	//insert texture update
	Vector2<double> position = playerController.getPosition ();
	this->setPosition ((float)position.x, (float)position.y);
	playerController.move ();
}

void Player::setPlayerTexture () {
	this->setTexture (texture);
}
