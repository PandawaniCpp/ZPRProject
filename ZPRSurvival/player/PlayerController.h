/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../classes/GameObjectController.h"
#include "Player.h"
#include "PlayerModel.h"
#include <SFML/System.hpp>

/**
	MVC's Controller for Player class. Gets input from Game, update rotation, mediate between Player and
	PlayerView, calculates movement and interactions.

	\base class: AnimatedObjectController
*/
class PlayerController: public GameObjectController<Player, Textures::PLAYER> {
public:
	// Default constructor.
	PlayerController ();

	// Default destructor.
	virtual ~PlayerController ();

	// Creates entity with EntityFactory
	//void createEntity (Entities::ID entityID, sf::Vector2f position);
	
	// Update player state, animation and effects
	void update ();

private:
	// Managers for different player's features.
	void controlStates ();
	void controlEffects ();

	
};

/**
	Humble Player's servant. Some say he relies on AnimatedObjectController's actions, but it is not true.
	He fully imitates them. But it would be rude not to mention his additional skills, such as
	Keyboard and Mouse input processing, ... fair enough. But remember, don't play cat and mouse with him.
*/
