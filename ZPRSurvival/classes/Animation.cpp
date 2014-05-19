/**
@date	15.05.2014

Part of the #TITLE survival game.

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Animation.h"

ResourceHolder<sf::Texture, Textures::ANIMATIONS> Animation::animationHolder = ResourceHolder<sf::Texture, Textures::ANIMATIONS> ();

Animation::Animation (Textures::ANIMATIONS id, std::string filename, sf::Vector3<int> frameData, bool repeatable, sf::Time duration) {
	insertFrameData (id, frameData);
	animationRepeat = repeatable;
	animationHolder.load (id, filename);
	currentAnimation = id;
	frameDuration = duration;

	this->setTexture (animationHolder.get (Textures::A_LOADING_ANIM));
}

Animation::~Animation () {
}