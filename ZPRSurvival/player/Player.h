/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../animated/AnimatedObject.h"

/**
	MVC's Model for Player class. Represents the state of the player.
	\see Player::State

	\base class: AnimatedObject
*/
class Player : public AnimatedObject {
public:
	// Current player's state options.
	enum State {
		IDLE = 0, MOVING, USING_ITEM, CRAFTING,
	};

	// Default constructor.
	Player ();

	// Default destructor.
	virtual ~Player ();

	// Getters

	Player::State getState ();
		
	// Setters

	void setState (Player::State state);

private:
	Player::State state = Player::IDLE;		// Holds current state.
};

/**
	The one and only Player class. When Player needs something, it is instantaneously done.
	His faithful squire, named gravely PlayerController, constantly calculate Player's new
	position, rotation, texture and keep track of his inventory, skills, atributes and carry
	his shiny sword. And shield. If he had one.... Maybe his older brother AnimatedObject
	knows something about it. Worth a shot.
*/