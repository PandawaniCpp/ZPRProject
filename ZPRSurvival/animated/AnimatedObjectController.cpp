/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "AnimatedObjectController.h"

AnimatedObjectController::AnimatedObjectController () {
	deltaTime = sf::Time::Zero;
}

AnimatedObjectController::~AnimatedObjectController () {
}

void AnimatedObjectController::calculateMove (AnimatedObject * animatedObject) const {
	// Get values from Model.
	int direction = animatedObject->getDirection ();
	float speed = animatedObject->getSpeed ();
	float rotation = animatedObject->getRotation ();
	Vector2<float> displacement = animatedObject->getDisplacement ();

	// #TODO Implement terrain speed modifiers.
		
	displacement.x = 0;
	displacement.y = 0;

	// Calculate displacement vector.		
	// #TODO optimization!
	if (direction) {
		if (direction == AnimatedObject::UP) {	
			displacement.x = speed * (float)sin (rotation * PI / 180);					// Going UP
			displacement.y = -speed * (float)cos (rotation * PI / 180);				
		}
		else {
			if (direction == (AnimatedObject::LEFT + AnimatedObject::UP)) {				// Going UP and LEFT
				displacement.x = speed * (float)sin ((rotation - 45) * PI / 180);		// Minus 45 degrees (moving diagonally)
				displacement.y = -speed * (float)cos ((rotation - 45) * PI / 180);
			}
			else if (direction == (AnimatedObject::RIGHT + AnimatedObject::UP)) {		// And so on...
				displacement.x = speed * (float)sin ((rotation + 45) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation + 45) * PI / 180);
			}
			else if (direction == AnimatedObject::LEFT) {
				displacement.x = speed * (float)sin ((rotation - 90) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation - 90) * PI / 180);
			}
			else if (direction == AnimatedObject::RIGHT) {
				displacement.x = speed * (float)sin ((rotation + 90) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation + 90) * PI / 180);
			}
			else if (direction == AnimatedObject::DOWN) {						
				displacement.x = -speed * (float)sin (rotation * PI / 180);
				displacement.y = speed * (float)cos (rotation * PI / 180);
			}
			else if (direction == (AnimatedObject::DOWN + AnimatedObject::LEFT)) {
				displacement.x = -speed * (float)sin ((rotation + 45) * PI / 180);		// Reverse rotation change.
				displacement.y = speed * (float)cos ((rotation + 45) * PI / 180);
			}
			else if (direction == (AnimatedObject::DOWN + AnimatedObject::RIGHT)) {
				displacement.x = -speed * (float)sin ((rotation - 45) * PI / 180);		// Same here.
				displacement.y = speed * (float)cos ((rotation - 45) * PI / 180);
			}
			else if (direction == (AnimatedObject::UP +			// When all keys are pressed, do nothing.
								AnimatedObject::DOWN +			// Empty if-instruction.
								AnimatedObject::LEFT +			// Technically it will never happen ("key ghosting").
								AnimatedObject::RIGHT)) {		
			}
			else if (direction == (AnimatedObject::UP +			// When UP and LEFT and RIGHT keys are pressed.
								AnimatedObject::LEFT +			// Then go UP.
								AnimatedObject::RIGHT)) {
				displacement.x = speed * (float)sin (rotation * PI / 180);		
				displacement.y = -speed * (float)cos (rotation * PI / 180);
			}
			else if (direction == (AnimatedObject::DOWN +		// When DOWN and LEFT and RIGHT keys are pressed.
								AnimatedObject::LEFT +			// Then go DOWN.
								AnimatedObject::RIGHT)) {
				displacement.x = -speed * (float)sin (rotation * PI / 180);
				displacement.y = speed * (float)cos (rotation * PI / 180);
			}
			else if (direction == (AnimatedObject::UP +			// When UP and DOWN and RIGHT keys are pressed.
								AnimatedObject::DOWN +			// Then go RIGHT.
								AnimatedObject::RIGHT)) {
				displacement.x = speed * (float)sin ((rotation + 90) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation + 90) * PI / 180);
			}
			else if (direction == (AnimatedObject::UP +  		// When UP and DOWN and LEFT keys are pressed.
								AnimatedObject::DOWN +			// Then go LEFT.
								AnimatedObject::LEFT)) {
				displacement.x = speed * (float)sin ((rotation - 90) * PI / 180);
				displacement.y = -speed * (float)cos ((rotation - 90) * PI / 180);
			}
		}
	}
	
	// Keep static frame.
	// Negative, because opposite direction to the sf::View.
	displacement *= -deltaTime.asSeconds ();

	// Set new values in Model.
	animatedObject->setSpeed (speed);
	animatedObject->setRotation (rotation);
	animatedObject->setDisplacement (displacement);
}

void AnimatedObjectController::calculateRotation (float & rotation, const Vector2<float> & rotationVector) const {
	// Save the difference between vector and current position.
	float deltaX = rotationVector.x;
	float deltaY = rotationVector.y;

	// Calc. vector rotation, 0 degrees == "up", clockwise.
	if (deltaX > 0) {
		if (deltaY < 0) {					// (0; 90) degrees
			rotation = (float)(atan (deltaX / -deltaY) * 180 / PI);
			return;
		}
		else {								// (90; 180) degrees
			rotation = (float)(atan (deltaY / deltaX) * 180 / PI + 90);
			return;
		}
	}
	else if (deltaX < 0) {
		if (deltaY > 0) {					// (180; 270) degrees
			rotation = (float)(atan (-deltaX / deltaY) * 180 / PI + 180);
			return;
		}
		else {								// (270; 360) degrees
			rotation = (float)(atan (-deltaY / -deltaX) * 180 / PI + 270);
			return;
		}
	}

	if (deltaX == 0) {			// Check if 'zeros'.
		if (deltaY <= 0)
			rotation = 0;		// Up, 0 deg.
		else
			rotation = 180;		// Down, 180 deg.
		return;
	}

	if (deltaY == 0) {			// Check if 'zeros'.
		if (deltaX < 0)
			rotation = 270;		// Left, 270 deg.
		else
			rotation = 90;		// Right, 90 deg.
		return;
	}
}

void AnimatedObjectController::move (Vector2<float> & position, const Vector2<float> & displacement) const {
	// Update position (referenced from the Model).
	position.x -= displacement.x;
	position.y -= displacement.y;

	// Set new position.
}