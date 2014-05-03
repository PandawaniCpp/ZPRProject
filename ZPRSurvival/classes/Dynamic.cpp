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
	float xAxisOffset = 0, yAxisOffset = 0;
	if (direction & Dynamic::DOWN && ~direction & Dynamic::UP)
		xAxisOffset = b2_pi;
	if (direction & Dynamic::LEFT)
		yAxisOffset += b2_pi / 2;
	if (direction & Dynamic::RIGHT)
		yAxisOffset -= b2_pi / 2;

	if (boxBody->GetAngle () < 0.f)
		boxBody->SetTransform (boxBody->GetPosition (), boxBody->GetAngle () + 2.f * b2_pi);

	float deltaAngle = abs (boxBody->GetAngle ()) / (2.0 * b2_pi);
	deltaAngle = abs (boxBody->GetAngle ()) - 2.f*b2_pi* (int)deltaAngle - rotation;
	
	if (abs(deltaAngle) < ANGLE_PRECISION) {
		boxBody->SetTransform (boxBody->GetPosition (), rotation);
		isRotating = false;
		b2Vec2 linearV = boxBody->GetLinearVelocity ();
		boxBody->SetAwake (false);
		boxBody->SetLinearVelocity (linearV);
	}
	else if (deltaAngle >= b2_pi || (deltaAngle <= 0 && deltaAngle >= -b2_pi)) {
		isRotating = true;
		boxBody->SetAngularVelocity (rotationSpeed);
	}
	else if (deltaAngle <= -b2_pi || (deltaAngle >= 0 && deltaAngle <= b2_pi)) {
		isRotating = true;
		boxBody->SetAngularVelocity (-rotationSpeed);
	}

	// #TODO REPAIR
	if (maxSpeedReached) {
		boxBody->SetLinearVelocity (b2Vec2 (maxSpeed * cos (boxBody->GetAngle () + xAxisOffset),
			-maxSpeed * sin (boxBody->GetAngle () + yAxisOffset)));
	}
	else {
		boxBody->ApplyForceToCenter (b2Vec2 (acceleration * cos (boxBody->GetAngle () + xAxisOffset),
											-acceleration * sin (boxBody->GetAngle () + yAxisOffset)),
											true);
		
		float actualSpeed = sqrt (pow (boxBody->GetLinearVelocity ().x, 2) +
								  pow (boxBody->GetLinearVelocity ().y, 2));
		if (actualSpeed >= maxSpeed) {
			maxSpeedReached = true;
		}
	}
	// #TODO REPAIR
}

void Dynamic::applyDirection (int dir) {
	if (dir == 0)
		direction = 0;
	else if (dir < 0) {
		if (direction & (-dir)) {
			direction += dir;
			maxSpeedReached = false;
		}
	}
	else if (dir > 0) {
		if (~direction & dir) {
			direction += dir;
			maxSpeedReached = false;
		}
	}
}

void Dynamic::applyForce (sf::Vector2f force) {
	this->boxBody->ApplyForceToCenter (b2Vec2 (force.x * cos (boxBody->GetAngle ()), force.y*sin (boxBody->GetAngle ())), true);
}

void Dynamic::setTargetRotation (float angle) {
	rotation = angle;
}