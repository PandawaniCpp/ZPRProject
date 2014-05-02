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
	void createEntity (Entities::ID entityID, sf::Vector2f position);
	
	// Update
	//void update ();

	/*
	// Sets default players parameters (origin etc.)
	void setPlayer ();

	// Calls other updates methods (rotation update, movement update...)
	// \param mousePosition - (x,y) of mouse cursor location => rotation update.
	void update (sf::Vector2<float> mousePosition);

	// Gets data from Model and updates View (and Sprite ofc).
	void prepareView ();
	
	// With given key information updated Player::direction by mixing AnimatedObject::Direction flags.
	// \param key - key pressed/released. Only called in Game::Playing state.
	void preparePlayerMove (const sf::Keyboard::Key key, const bool isPressed); 	

	// Pass own pointer to AnimatedObjectController::move method.
	void calculatePlayerMove ();

	// With given mousePosition calls AnimatedObjectController::calculateRotation.
	// Also updated Model's rotation.
	void calculatePlayerRotation (sf::Vector2<float> mousePosition);

	// Updated Model's position.
	void setPosition (sf::Vector2<float> position);	
	
	// Getters

	Player * getPlayer ();
	PlayerView * getPlayerView ();

private:
	Player * player;			// Pointers to Model and View.
	PlayerView * playerView;	// Both controlled by Controller (yeah...)*/
};

/**
	Humble Player's servant. Some say he relies on AnimatedObjectController's actions, but it is not true.
	He fully imitates them. But it would be rude not to mention his additional skills, such as
	Keyboard and Mouse input processing, ... fair enough. But remember, don't play cat and mouse with him.
*/
