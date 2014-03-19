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
