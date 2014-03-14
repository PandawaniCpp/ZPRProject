#include "BaseController.h"


BaseController::BaseController () {
	position.x = 0;
	position.y = 0;
	rotation = 0;
	forSpeed = 0.0;
	revSpeed = 0.0;
	direction = 0;
	phase = STOP;
}

BaseController::BaseController (BaseController & baseController) {
	position.x = baseController.position.x;
	position.y = baseController.position.y;
	rotation = baseController.rotation;
	forSpeed = baseController.forSpeed;
	revSpeed = baseController.revSpeed;
	direction = baseController.direction;
	phase = baseController.phase;
}


BaseController::~BaseController () {
}

//object manipulators ==============================================
void BaseController::prepareMove (int direction, bool isPressed) {
	if (isPressed)		//add or remove new directions
		this->direction = this->direction | direction;
	else 
		this->direction = this->direction ^ direction;

	switch (phase) {		//declare new movement phase
		case STOP:
			if (this->direction != 0) {		//want to move
				if (~this->direction & DOWN) {
					phase = ACCEL_FWD;		//move forward and/or left/right
				}
				else if ((this->direction & UP) == 0) {
					phase = ACCEL_BWD;		//move backward
				}
			}
			break;
		case ACCEL_FWD:
			if ((this->direction & 15) == 0)	//nothing is pressed
				phase = DECEL_FWD;				//braking
			else if (~this->direction & DOWN)		//any except DOWN
				break;								//nothing to change
			else if ((this->direction & UP) == 0) {		//DOWN and any except UP		
				phase = ACCEL_BWD;						//rapidly slowing
			}
			break;
		case ACCEL_BWD:
			if ((this->direction & 15) == 0) 	//nothing is pressed
				phase = DECEL_BWD;				//braking
			else if (~this->direction & UP)			//any except UP
				break;								//nothing to change
			else if ((this->direction & DOWN) == 0) 		//UP and any except DOWN		
				phase = ACCEL_FWD;						//rapidly slowing
			break;
		case DECEL_FWD:
			if (this->direction == 0)			//nothing is pressed
				break;							//still braking
			else if (~this->direction & DOWN)		//any except DOWN
				phase = ACCEL_FWD;					//start accelerating forward
			else if ((this->direction & UP) == 0)		//DOWN and any except UP
				phase = ACCEL_BWD;						//start accelerating
			break;
		case DECEL_BWD:
			if (this->direction == 0)			//nothing is pressed
				break;							//still braking
			else if (~this->direction & UP)			//any except UP
				phase = ACCEL_BWD;					//start accelerating forward
			else if ((this->direction & DOWN) == 0)		//UP and any except DOWN
				phase = ACCEL_FWD;						//start accelerating
			break;
		default:
			break;
	}
}

void BaseController::calculateMove () {
	switch (phase) {		//calculate speed
		case STOP:
			break;
		case ACCEL_FWD:
			if (forSpeed >= maxFSpeed)			//keep running
				forSpeed = maxFSpeed;
			else if (revSpeed > 0) {
				revSpeed /= 5;		//rapidly lowering reverse speed
				if (revSpeed < 1)
					revSpeed = 0;
			}
			else if (forSpeed >= 0) {
				forSpeed += 50; //accelerating forward
				if (forSpeed > maxFSpeed)
					forSpeed = maxFSpeed;
			}
			break;
		case ACCEL_BWD:
			if (revSpeed >= maxRSpeed)
				revSpeed = maxRSpeed;
			else if (forSpeed > 0) {
				forSpeed /= 5;
				if (forSpeed < 1)
					forSpeed = 0;
			}
			else if (revSpeed >= 0) {
				revSpeed += 35;
				if (revSpeed > maxRSpeed)
					revSpeed = maxRSpeed;
			}
			break;
		case DECEL_FWD:
			if (forSpeed < 1) {
				forSpeed = 0;
				phase = STOP;
			}
			else if (forSpeed >= 1)
				forSpeed /= 1.5;
			break;
		case DECEL_BWD:
			if (revSpeed < 1) {
				revSpeed = 0;
				phase = STOP;
			}
			else if (revSpeed >= 1)
				revSpeed /= 1.5;
			break;
		default:
			break;
	}

	if (forSpeed)
		this->displacement.x = forSpeed;
	else if (revSpeed)
		this->displacement.x = -revSpeed;
}

void BaseController::move () {
	Vector2<double> tempDisplacement = displacement * (double)deltaTime.asSeconds ();
	position.x += tempDisplacement.x;
	position.y += tempDisplacement.y;
}

void BaseController::rotate (double newAngle) {
	rotation = newAngle;
}

void BaseController::setDeltaTime (sf::Time deltaTime) {
	this->deltaTime = deltaTime;
}

//getters ==========================================================
Vector2<double> BaseController::getPosition () {
	return position;
}

double BaseController::getRotation () {
	return rotation;
}

double BaseController::getFSpeed () {
	return forSpeed;
}

double BaseController::getRSpeed () {
	return revSpeed;
}

int BaseController::getDirection () {
	return direction;
}

int BaseController::getPhase () {
	return phase;
}