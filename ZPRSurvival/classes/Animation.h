/**
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../interface/ResourceHolder.h"
#include "../interface/ResourcesID.h"
#include "Animated.h"

class Animation : public Animated <Textures::ANIMATIONS> {
public:
	// Container for all animations (except world object animations)
	static ResourceHolder <sf::Texture, Textures::ANIMATIONS> animationHolder;

	// Constructor.
	Animation (Textures::ANIMATIONS id, std::string filename, sf::Vector3<int> frameData, bool repeatable, sf::Time duration);

	// Default destructor.
	~Animation ();
};

