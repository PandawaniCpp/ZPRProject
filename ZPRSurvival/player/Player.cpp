#include "Player.h"


Player::Player ()
{
}


Player::~Player ()
{
}

void Player::SetPlayer (void)
{
	texture.loadFromFile ("player.png");
	this->setTexture (texture);
	//this->setTextureRect (sf::IntRect (0, 0, 30, 30));
	//this->setColor (sf::Color (255, 255, 255, 200));
	this->setPosition (100, 100);
}
