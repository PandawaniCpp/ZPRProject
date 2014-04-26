/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../animated/AnimatedObjectView.h"
#include "../interface/ResourceHolder.h"
#include "../interface/ResourcesID.h"

/**
	MVC's View for Player class. Responsible for drawing player.

	\base class: AnimatedObjectView
*/
class PlayerView : public AnimatedObjectView {
public:
	// Default constructor.
	PlayerView ();

	// Default destructor.
	virtual ~PlayerView ();

	// Overloaded sf::Sprite draw() method for Player.
	virtual void draw (sf::RenderWindow& window) const;

	// Connects Texture::ID with row number of the .png file.
	std::map<Textures::ID, int> textureIdRow;

private:
	// Hold all player's textures listed by Textures::ID.
	ResourceHolder<Texture, Textures::ID> textureHolder;
};

