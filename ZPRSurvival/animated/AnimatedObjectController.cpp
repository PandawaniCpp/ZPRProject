#include "AnimatedObjectController.h"


AnimatedObjectController::AnimatedObjectController () {
	deltaTime = Time::Zero;
}

AnimatedObjectController::~AnimatedObjectController () {
}

/************* object manipulators **************/
void AnimatedObjectController::calculateMove (AnimatedObject * animatedObject) {
	int direction = animatedObject->getDirection ();
	float speed = animatedObject->getSpeed ();
	float rotation = animatedObject->getRotation ();
	Vector2<float> displacement = animatedObject->getDisplacement ();

		// #TODO
	//implement terrain speed modifiers
		
		//calculate displacement vector
	if (direction) {
		if ((direction - AnimatedObject::UP == 0) || (~direction - AnimatedObject::DOWN == 0)) {	
			displacement.x = speed * (float)sin (rotation * PI / 180);				//going UP
			displacement.y = -speed * (float)cos (rotation * PI / 180);				//also when UP and LEFT and RIGHT keys are pressed
		}
		else {
			if (direction - AnimatedObject::LEFT - AnimatedObject::UP == 0) {		//going UP and LEFT
				displacement.x = speed * (float)sin ((rotation - 45) * PI / 180);	//minus 45 degrees (PlayerState::State::MOVING diagonally)
				displacement.y = -speed * (float)cos ((rotation - 45) * PI / 180);
			}
			else if (direction - AnimatedObject::RIGHT - AnimatedObject::UP == 0) {		//and so on...
				displacement.x = speed * (float)sin ((rotation + 45) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation + 45) * PI / 180);
			}
			else if ((direction - AnimatedObject::LEFT == 0) || (~direction - AnimatedObject::RIGHT == 0)) {
				displacement.x = speed * (float)sin ((rotation - 90) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation - 90) * PI / 180);
			}
			else if ((direction - AnimatedObject::RIGHT == 0) || (~direction - AnimatedObject::LEFT == 0)) {
				displacement.x = speed * (float)sin ((rotation + 90) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation + 90) * PI / 180);
			}
			else if ((direction - AnimatedObject::DOWN == 0) || (~direction - AnimatedObject::UP == 0)) {						//going down
				displacement.x = -speed * (float)sin (rotation * PI / 180);
				displacement.y = speed * (float)cos (rotation * PI / 180);
			}
			else if (direction - AnimatedObject::DOWN - AnimatedObject::LEFT == 0) {
				displacement.x = -speed * (float)sin ((rotation + 45) * PI / 180);	//reverse rotation change
				displacement.y = speed * (float)cos ((rotation + 45) * PI / 180);
			}
			else if (direction - AnimatedObject::DOWN - AnimatedObject::RIGHT == 0) {
				displacement.x = -speed * (float)sin ((rotation - 45) * PI / 180);	//same here
				displacement.y = speed * (float)cos ((rotation - 45) * PI / 180);
			}
		}
	}
	else {
		displacement.x = 0;
		displacement.y = 0;
	}
	
		//keep static frame
	displacement *= deltaTime.asSeconds ();

	animatedObject->setSpeed (speed);
	animatedObject->setRotation (rotation);
	animatedObject->setDisplacement (displacement);
}

void AnimatedObjectController::calculateRotation (float & rotation, const Vector2<float> & rotationVector) {
	float deltaX = rotationVector.x;
	float deltaY = rotationVector.y;

	//calc. vector rotation. 0 degrees == "AnimatedState::UP", clockwise.
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
			rotation = 0;		//AnimatedState::UP, 0 deg.
		else
			rotation = 180;		//AnimatedState::DOWN, 180 deg.
		return;
	}

	if (deltaY == 0) {			//check if 'zeros'
		if (deltaX < 0)
			rotation = 270;		//AnimatedState::LEFT, 270 deg.
		else
			rotation = 90;		//AnimatedState::RIGHT, 90 deg.
		return;
	}
}

void AnimatedObjectController::move (const int direction, Vector2<float> & position, const Vector2<float> & displacement) {
	position.x += displacement.x;
	position.y += displacement.y;
}

void AnimatedObjectController::setDeltaTime (Time deltaTime) {
	this->deltaTime = deltaTime;
}