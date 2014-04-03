#include "PlayerController.h"

PlayerController::PlayerController () {
	player = new Player;
	playerView = new PlayerView;
}

PlayerController::~PlayerController () {
}

void PlayerController::update (Vector2i mousePosition) {
		//insert texture update

		//rotation update
	calculatePlayerRotation (mousePosition);

		//displacement AnimatedState::UPdate
	if ((player->getSpeed() != 0) || (player->getDirection() != 0))
		calculatePlayerMove ();

		//position update
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
	
	if (key == sf::Keyboard::W)						//how the player move...
		directionChange = AnimatedObject::UP;
	else if (key == sf::Keyboard::S)
		directionChange = AnimatedObject::DOWN;
	else if (key == sf::Keyboard::A)
		directionChange = AnimatedObject::LEFT;
	else if (key == sf::Keyboard::D)
		directionChange = AnimatedObject::RIGHT;	//...

	if (isPressed)		//add or remove new directions
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
	float deltaX = mousePosition.x - player->getPosition ().x;
	float deltaY = mousePosition.y - player->getPosition ().y;
	Vector2<float> rotationVector (deltaX, deltaY);
	float rotation = 0;

	calculateRotation (rotation, rotationVector);

	player->setRotation (rotation);
}

void PlayerController::setPlayer () {
	playerView->setOrigin (player->getSize ().x / 2, player->getSize ().y / 2);	//to rotate relatively to the player center
}

Player * PlayerController::getPlayer () {
	return player;
}

PlayerView * PlayerController::getPlayerView () {
	return playerView;
}