/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "GameObject.h"

template <class Identifier>
/**
	MVC's View for Animated class. Provides animation attributes for derived classes.

	\ base class: GameObject
	\ derived:    Player, Creature, Item
*/
class Animated : virtual public GameObject {
public:
	// Stores frame count of particular animation (texture).
	// x-param : frame width
	// y-param : frame height
	// z-param : frame count
	static std::map<Identifier, sf::Vector3<int>> frameData;

	// Inserts new animation data for texture: frame size,
	// frame count (which row, how many in a row) and texture id.
	static void insertAnimationData (Identifier textureID, sf::Vector3<int> frameInfo);

	// Default constructor.
	Animated ();

	// Default destructor.
	virtual ~Animated ();

	// Animation handling.
	void animate (sf::Time dt);

	// Change animation to draw.
	void changeAnimation (Identifier textureID);

	// Reset frames and times for next animation.
	void resetAnimation ();

	// Get current aniumation
	Identifier getCurrentAnimation ();

protected:
	Identifier currentAnimation;		// Animation state.
	sf::Time frameDuration;				// Time per frame (duration / frame count)
	sf::Time elapsedTime;				// Time passed (controls when to switch frame)
	int frameNumber;					// Number of frame actually written.
	bool animationRepeat;				// Animation is repeatable.
	//bool animationActive;				// #TODO Check if neccessary
};

template <class Identifier>
std::map<Identifier, sf::Vector3<int>> Animated<Identifier>::frameData = std::map<Identifier, sf::Vector3<int>> ();

template <class Identifier>
void Animated<Identifier>::insertAnimationData (Identifier textureID, sf::Vector3<int> frameInfo) {
	frameData.insert (std::make_pair (textureID, frameInfo));
}

template <class Identifier>
Animated<Identifier>::Animated (){
}

template <class Identifier>
Animated<Identifier>::~Animated () {
}

template <class Identifier>
void Animated<Identifier>::animate (sf::Time dt) {
	// #TODO COMMENTS!!!!!!!!!!!
	sf::Time timePerFrame = frameDuration / static_cast<float>(frameData[currentAnimation].z);
	elapsedTime += dt;
	sf::Vector2i textureBounds (this->getTexture ()->getSize ());
	sf::IntRect textureRect = this->getTextureRect ();

	if (frameNumber == 0)
		textureRect = sf::IntRect (0, 0, frameData[currentAnimation].x, frameData[currentAnimation].y);
	while (elapsedTime >= timePerFrame && (frameNumber <= frameData[currentAnimation].z || animationRepeat)) {
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
			textureRect.left = 0;
		elapsedTime -= timePerFrame;
		if (animationRepeat) {
			frameNumber = (frameNumber + 1) % frameData[currentAnimation].z;
			if (frameNumber == 0)
				textureRect = sf::IntRect (0, 0, frameData[currentAnimation].x, frameData[currentAnimation].y);
		}
		else {
			frameNumber++;
		}
	}
	this->setTextureRect (textureRect);
}

template <class Identifier>
void Animated<Identifier>::changeAnimation (Identifier textID) {
	currentAnimation = textID;
}

template <class Identifier>
void Animated<Identifier>::resetAnimation () {
	elapsedTime = sf::Time::Zero;
	frameNumber = 0;
}

template <class Identifier>
Identifier Animated<Identifier>::getCurrentAnimation () {
	return currentAnimation;
}
