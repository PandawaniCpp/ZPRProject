#include "BaseController.h"


BaseController::BaseController () {
	position.x = 0;
	position.y = 0;
	rotation = 0;
	speed = 0.0;
	direction = 0;
}

BaseController::BaseController (BaseController & baseController) {
	position.x = baseController.position.x;
	position.y = baseController.position.y;
	rotation = baseController.rotation;
	speed = baseController.speed;
	direction = baseController.direction;
}


BaseController::~BaseController () {
}

//object manipulators ==============================================
void BaseController::prepareMove (int direction, bool isPressed) {
	displacement.x = 0.f;		//reset displacement
	displacement.y = 0.f;

	if (isPressed)		//add or remove new directions
		this->direction = this->direction | direction;
	else
		this->direction = this->direction ^ direction;

	if (this->direction & UP)			//calculate new position
		displacement.y -= speed;
	if (this->direction & DOWN)
		displacement.y += speed;
	if (this->direction & LEFT)
		displacement.x -= speed;
	if (this->direction & RIGHT)
		displacement.x += speed;
}

void BaseController::move () {
	position.x += displacement.x;
	position.y += displacement.y;
}

void BaseController::rotate (double newAngle) {
	rotation = newAngle;
}

//getters ==========================================================
Vector2<double> BaseController::getPosition () {
	return position;
}

double BaseController::getRotation () {
	return rotation;
}