/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/System/Vector2.hpp>

/**
	MVC's Model for Player class. Represents the state of the player.
	\see Player::State

	\base class: AnimatedObject
*/
class PlayerModel { //: public AnimatedObject {
public:
	// Current player's state options.
	enum State {
		IDLE = 0, MOVING, USING_ITEM, CRAFTING,
	};

	// Default constructor.
	PlayerModel ();

	// Default destructor.
	virtual ~PlayerModel ();

	// Getters

	PlayerModel::State getState ();
	sf::Vector2<float> getOffset ();
		
	// Setters

	void setState (PlayerModel::State state);
	void setOffset (sf::Vector2<float> offset);

private:
	PlayerModel::State state = PlayerModel::IDLE;		// Holds current state.
	sf::Vector2<float> offset;		// Additional displacement when moving mouse away from the player.
};

/**
	The one and only Player class. When Player needs something, it is instantaneously done.
	His faithful squire, named gravely PlayerController, constantly calculate Player's new
	position, rotation, texture and keep track of his inventory, skills, atributes and carry
	his shiny sword. And shield. If he had one.... Maybe his older brother AnimatedObject
	knows something about it. Worth a shot.
*/