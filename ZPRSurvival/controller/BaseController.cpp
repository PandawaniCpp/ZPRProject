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

/************* object manipulators **************/
void BaseController::prepareMove (int direction) {
	this->direction = direction;

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
		
		//calculate displacement vector
	if (forSpeed) {
		displacement.x = forSpeed * (float)sin (rotation * PI / 180);
		displacement.y = -forSpeed * (float)cos (rotation * PI / 180);
	}
	else if (revSpeed) {		// !!! changed sign !!!
		displacement.x = -revSpeed * (float)sin (rotation * PI / 180);
		displacement.y = revSpeed * (float)cos (rotation * PI / 180);
	}
	else {
		displacement.x = 0;
		displacement.y = 0;
	}
	
		//keep static frame
	displacement *= deltaTime.asSeconds ();
}

void BaseController::calculateRotation (Vector2<float> destination) {
	float deltaX = destination.x - position.x;
	float deltaY = destination.y - position.y;

	//calc. vector rotation. 0 degrees == "up", clockwise.
	if (deltaX > 0) {
		if (deltaY < 0) {					//(0; 90) degrees
			rotation = (float)(atan (deltaX / -deltaY) * 180 / PI);
			return;
		}
		else {								//(90; 180) degrees
			rotation = (float)(atan (deltaY / deltaX) * 180 / PI + 90);
			return;
		}
	}
	else if (deltaX < 0) {
		if (deltaY > 0) {					//(180; 270) degrees
			rotation = (float)(atan (-deltaX / deltaY) * 180 / PI + 180);
			return;
		}
		else {								//(270; 360) degrees
			rotation = (float)(atan (-deltaY / -deltaX) * 180 / PI + 270);
			return;
		}
	}

	if (deltaX == 0) {			//check if 'zeros'
		if (deltaY <= 0)
			rotation = 0;		//UP, 0 deg.
		else
			rotation = 180;		//DOWN, 180 deg.
		return;
	}

	if (deltaY == 0) {			//check if 'zeros'
		if (deltaX < 0)
			rotation = 270;		//LEFT, 270 deg.
		else
			rotation = 90;		//RIGHT, 90 deg.
		return;
	}
}

void BaseController::move () {
	position.x += displacement.x;
	position.y += displacement.y;
}

void BaseController::setPosition (Vector2<float> position) {
	this->position = position;
}

void BaseController::rotate (float angle) {
	rotation += angle;
}

void BaseController::setRotation (float rotation) {
	this->rotation = rotation;
}

void BaseController::setDeltaTime (Time deltaTime) {
	this->deltaTime = deltaTime;
}

/***********  getters ***********/
Vector2<float> BaseController::getPosition () {
	return position;
}

Vector2<float> BaseController::getDisplacement () {
	return displacement;
}

float BaseController::getRotation () {
	return rotation;
}

float BaseController::getFSpeed () {
	return forSpeed;
}

float BaseController::getRSpeed () {
	return revSpeed;
}

int BaseController::getDirection () {
	return direction;
}

int BaseController::getPhase () {
	return phase;
}