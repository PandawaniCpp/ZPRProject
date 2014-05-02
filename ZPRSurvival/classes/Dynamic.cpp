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

void Dynamic::applyForce (sf::Vector2f force) {

	this->boxBody->ApplyForceToCenter (b2Vec2 (force.x * cos (boxBody->GetAngle ()), force.y*sin (boxBody->GetAngle ())), true);
}

void Dynamic::applyRotation (float angularForce) {
	//this->boxBody->ApplyAngularImpulse (angularForce, true);
	boxBody->ApplyTorque (angularForce, true);
}