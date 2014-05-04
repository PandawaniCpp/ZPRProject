/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../classes/Animated.h"
#include "../classes/Dynamic.h"
#include "../classes/Effectable.h"
#include "../interface/ResourceHolder.h"
#include "../interface/ResourcesID.h"

/**
	MVC's View for Player class. Responsible for drawing player.

	\base class: Animated, Dynamic, Effectable
*/
class Player : public Animated<Textures::PLAYER>, public Dynamic, public Effectable {
	friend class Game;
public:
	// Default constructor.
	Player ();

	// Prefab constructor.
	Player (GameObject::Prefab prefab);

	// Default destructor.
	~Player ();

	// Overloaded sf::Sprite draw() method for Player.
	virtual void draw (sf::RenderWindow * window) const;
};

