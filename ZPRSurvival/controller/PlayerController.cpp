#include "PlayerController.h"

PlayerController::PlayerController () {
	forSpeed = 0;
	revSpeed = 0;
	maxFSpeed = 400;
	maxRSpeed = 250;
	size.x = 50;
	size.y = 50;
}

PlayerController::~PlayerController () {
}

void PlayerController::preparePlayerMove (int direction, bool isPressed) {
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

void PlayerController::setPlayerPosition (Vector2<int> position) {
	this->position.x = (float)position.x;
	this->position.y = (float)position.y;
}

void PlayerController::setMousePosition (Vector2i position) {
	mousePosition = position;
}

void PlayerController::calculatePlayerRotation () {
	float deltaX = mousePosition.x - position.x;
	float deltaY = mousePosition.y - position.y;

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

/**************** getters ****************/
playerState PlayerController::getState () {
	return state;
}

Vector2<float> PlayerController::getSize () {
	return size;
}

Vector2i PlayerController::getMousePosition () {
	return mousePosition;
}
