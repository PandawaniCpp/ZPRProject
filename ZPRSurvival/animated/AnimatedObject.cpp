/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "AnimatedObject.h"

AnimatedObject::AnimatedObject () {
}

AnimatedObject::~AnimatedObject () {
}

// Getters

sf::Vector2<float> AnimatedObject::getDisplacement () {
	return displacement;
}

sf::Vector2<float> AnimatedObject::getSize () {
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

//Setters

void AnimatedObject::setDisplacement (sf::Vector2<float> displacement) {
	this->displacement = displacement;
}

void AnimatedObject::setSize (sf::Vector2<float> size) {
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