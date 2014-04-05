/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "SurvivalObject.h"

SurvivalObject::SurvivalObject () {
}

SurvivalObject::~SurvivalObject (){
}

//getters
Vector2<float> SurvivalObject::getPosition () {
	return position;
}

//setters
void SurvivalObject::setPosition (Vector2<float> position) {
	this->position = position;
}
