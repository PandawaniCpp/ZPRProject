#include "BaseController.h"


BaseController::BaseController () {
	deltaTime = Time::Zero;
}

/*BaseController::BaseController (BaseController & baseController) {
	deltaTime = baseController.deltaTime;
}*/

BaseController::~BaseController () {
}

/************* object manipulators **************/
void BaseController::prepareMove (int & direction, MovingPhase & phase) {
	switch (phase) {		//declare new movement phase
		case STOP:
			if (direction != 0) {		//want to move
				if (~direction & DOWN) {
					phase = ACCEL_FWD;		//move forward and/or left/right
				}
				else if ((direction & UP) == 0) {
					phase = ACCEL_BWD;		//move backward
				}
			}
			break;
		case ACCEL_FWD:
			if ((direction & 15) == 0)	//nothing is pressed
				phase = DECEL_FWD;				//braking
			else if (~direction & DOWN)		//any except DOWN
				break;								//nothing to change
			else if ((direction & UP) == 0) {		//DOWN and any except UP		
				phase = ACCEL_BWD;						//rapidly slowing
			}
			break;
		case ACCEL_BWD:
			if ((direction & 15) == 0) 	//nothing is pressed
				phase = DECEL_BWD;				//braking
			else if (~direction & UP)			//any except UP
				break;								//nothing to change
			else if ((direction & DOWN) == 0) 		//UP and any except DOWN		
				phase = ACCEL_FWD;						//rapidly slowing
			break;
		case DECEL_FWD:
			if (direction == 0)			//nothing is pressed
				break;							//still braking
			else if (~direction & DOWN)		//any except DOWN
				phase = ACCEL_FWD;					//start accelerating forward
			else if ((direction & UP) == 0)		//DOWN and any except UP
				phase = ACCEL_BWD;						//start accelerating
			break;
		case DECEL_BWD:
			if (direction == 0)			//nothing is pressed
				break;							//still braking
			else if (~direction & UP)			//any except UP
				phase = ACCEL_BWD;					//start accelerating forward
			else if ((direction & DOWN) == 0)		//UP and any except DOWN
				phase = ACCEL_FWD;						//start accelerating
			break;
		default:
			break;
	}
}

void BaseController::calculateMove (AnimatedObject * animatedObject) {
	MovingPhase phase = animatedObject->getPhase ();
	float forSpeed = animatedObject->getForSpeed ();
	float revSpeed = animatedObject->getRevSpeed ();
	float maxFSpeed = animatedObject->getMaxFSpeed ();
	float maxRSpeed = animatedObject->getMaxRSpeed ();
	float rotation = animatedObject->getRotation ();
	Vector2<float> displacement = animatedObject->getDisplacement ();

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

	animatedObject->setPhase (phase);
	animatedObject->setForSpeed (forSpeed);
	animatedObject->setRevSpeed (revSpeed);
	animatedObject->setMaxFSpeed (maxFSpeed);
	animatedObject->setMaxRSpeed (maxRSpeed);
	animatedObject->setRotation (rotation);
	animatedObject->setDisplacement (displacement);
}

void BaseController::calculateRotation (float & rotation, const Vector2<float> & rotationVector) {
	float deltaX = rotationVector.x;
	float deltaY = rotationVector.y;

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

void BaseController::move (const int direction, Vector2<float> & position, const Vector2<float> & displacement) {
	position.x += displacement.x;
	position.y += displacement.y;
}

void BaseController::setDeltaTime (Time deltaTime) {
	this->deltaTime = deltaTime;
}