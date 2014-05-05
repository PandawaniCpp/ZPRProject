/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Dynamic.h"

Dynamic::Dynamic () {
}

Dynamic::~Dynamic () {
}

void Dynamic::update () {
	// Force offsets depending on direction.
	float xAxisOffset = 0.f, yAxisOffset = 0.f, finalOffset = 0;
	bool xAxisOffsetActive = true;

	// Check for xAxisOffset
	if (direction & Dynamic::DOWN && ~direction & Dynamic::UP)
		xAxisOffset = b2_pi;
	else if (direction & Dynamic::UP && ~direction & Dynamic::DOWN)
		xAxisOffset = 0;
	else
		xAxisOffsetActive = false;
		
	// Check for yAxisOffset
	if (direction & Dynamic::LEFT)
		yAxisOffset += b2_pi / 2.f;
	if (direction & Dynamic::RIGHT)
		yAxisOffset -= b2_pi / 2.f;

	// Keep offset positive.
	if (yAxisOffset < 0.f)
		yAxisOffset += 2.f * b2_pi;

	// When 2 offsets collide, take resultant offse
	if (yAxisOffset && xAxisOffsetActive) {
		finalOffset = (yAxisOffset + xAxisOffset) / 2.f;
		if (direction & Dynamic::UP && direction & Dynamic::RIGHT)
			finalOffset += b2_pi;
	}
	else			// In other case, just take nonzero one.
		finalOffset = std::max (yAxisOffset, xAxisOffset);

	// Wanna always keep rotation value positive
	if (boxBody->GetAngle () < 0.f)
		boxBody->SetTransform (boxBody->GetPosition (), boxBody->GetAngle () + 2.f * b2_pi);

	// Calculating difference between current rotation and target rotation
	float deltaAngle = abs (boxBody->GetAngle ()) / (2.0 * b2_pi);
	deltaAngle = abs (boxBody->GetAngle ()) - 2.f*b2_pi* (int)deltaAngle - rotation;
	
	// Rotating object
	isRotating = true;
	if (abs (deltaAngle) < ANGLE_PRECISION) {		// If object is heading (almost) when the cursor is...
		if (abs (deltaAngle) < b2_epsilon)
			isRotating = false;
		else
			boxBody->SetTransform (boxBody->GetPosition (), rotation);		//... set target rotation immediately
	}
	else if (deltaAngle >= b2_pi || (deltaAngle <= 0 && deltaAngle >= -b2_pi)) {
		boxBody->SetAngularVelocity (rotationSpeed);	// Rotate counter clockwise
	}
	else if (deltaAngle <= -b2_pi || (deltaAngle >= 0 && deltaAngle <= b2_pi)) {
		boxBody->SetAngularVelocity (-rotationSpeed);		// Rptate clockwise
	}
	

	// Get movement params.
	/*b2Vec2 currentVelocity = boxBody->GetLinearVelocity ();
	float currentSpeed = HYPOTENUSE (currentVelocity.x, currentVelocity.y);
	b2Vec2 currentForce = boxBody->GetForce ();	
	float currentForceValue = HYPOTENUSE (currentForce.x, currentForce.y);*/

	// Check if any key is pressed
	if (direction) 
		isAccelerating = true;
	else
		isAccelerating = false; 

	// If so, apply force in proper direction.
	if (isAccelerating) {
		// Perhaps multiply force if object is running.
		float accel = this->acceleration;
		if (isRunning)
			accel *= runModifier;

		// Force appliance
		boxBody->ApplyForceToCenter (b2Vec2 (accel * cos (boxBody->GetAngle () + finalOffset),
											-accel * sin (boxBody->GetAngle () + finalOffset)),
											true);
	}
}

void Dynamic::applyDirection (int dir) {
	if (dir == 0)
		direction = 0;
	else if (dir < 0) {
		if (direction & (-dir)) {
			direction += dir;
		}
	}
	else if (dir > 0) {
		if (~direction & dir) {
			direction += dir;
		}
	}
}

void Dynamic::setTargetRotation (float angle) {
	rotation = angle;
}

void Dynamic::setRunning (bool isRunning) {
	this->isRunning = isRunning;
}