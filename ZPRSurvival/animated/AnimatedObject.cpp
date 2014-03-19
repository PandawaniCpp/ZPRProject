#include "AnimatedObject.h"

AnimatedObject::AnimatedObject () {
}

AnimatedObject::~AnimatedObject () {
}

//getters
Vector2<float> AnimatedObject::getDisplacement () {
	return displacement;
}

Vector2<float> AnimatedObject::getSize () {
	return size;
}

float AnimatedObject::getMaxFSpeed () {
	return maxFSpeed;
}

float AnimatedObject::getMaxRSpeed () {
	return maxRSpeed;
}

float AnimatedObject::getForSpeed () {
	return forSpeed;
}

float AnimatedObject::getRevSpeed () {
	return revSpeed;
}

float AnimatedObject::getRotation () {
	return rotation;
}

int AnimatedObject::getDirection () {
	return direction;
}

MovingPhase AnimatedObject::getPhase () {
	return phase;
}

//setters
void AnimatedObject::setDisplacement (Vector2<float> displacement) {
	this->displacement = displacement;
}

void AnimatedObject::setSize (Vector2<float> size) {
	this->size = size;
}

void AnimatedObject::setMaxFSpeed (float maxFSpeed) {
	this->size = size;
}

void AnimatedObject::setMaxRSpeed (float maxRSpeed) {
	this->maxRSpeed = maxRSpeed;
}

void AnimatedObject::setForSpeed (float forSpeed) {
	this->forSpeed = forSpeed;
}

void AnimatedObject::setRevSpeed (float revSpeed) {
	this->revSpeed = revSpeed;
}

void AnimatedObject::setRotation (float rotation) {
	this->rotation = rotation;
}

void AnimatedObject::setDirection (int direction) {
	this->direction = direction;
}

void AnimatedObject::setPhase (MovingPhase phase) {
	this->phase = phase;
}

