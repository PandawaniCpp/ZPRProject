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

float AnimatedObject::getSpeed () {
	return speed;
}

float AnimatedObject::getRotation () {
	return rotation;
}

int AnimatedObject::getDirection () {
	return direction;
}

//setters
void AnimatedObject::setDisplacement (Vector2<float> displacement) {
	this->displacement = displacement;
}

void AnimatedObject::setSize (Vector2<float> size) {
	this->size = size;
}

void AnimatedObject::setSpeed (float revSpeed) {
	this->speed = revSpeed;
}

void AnimatedObject::setRotation (float rotation) {
	this->rotation = rotation;
}

void AnimatedObject::setDirection (int direction) {
	this->direction = direction;
}