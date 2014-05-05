/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Box2D/Dynamics/b2World.h>
#include "../interface/ResourcesID.h"
#include "../interface/ResourceHolder.h"
#include "../interface/EntityFactory.h"
//#include "GameObject.h"
//#define PI 3.14159265		//converting degrees <-> radians

template <class Type, class Identifier>
/** 
	MVC's Controller for GameObject class. 
*/
class GameObjectController {
public:
	//friend class Game
	//typedef Type* entityPtr;

	// Time for one tick. Initialized in Game::run()
	static sf::Time deltaTime;

	// Default constructor.
	GameObjectController ();

	// Default destructor.
	virtual ~GameObjectController ();

	// Update all data about enitites
	void updateEntities ();
	
	// Overloaded access operator for getting entities.
	Type* operator[](std::size_t index);

protected:
	ResourceHolder<sf::Texture, Identifier> textureHolder;		// Template for all different texture holders
	std::vector<Type*> entityHolder;			// Holds all entities
};

template <class Type, class Identifier>
sf::Time GameObjectController<Type, Identifier>::deltaTime = sf::Time::Zero;

template <class Type, class Identifier>
GameObjectController<Type, Identifier>::GameObjectController () {
}

template <class Type, class Identifier>
GameObjectController<Type, Identifier>::~GameObjectController () {
	
}

template <class Type, class Identifier>
void GameObjectController<Type, Identifier>::updateEntities () {
	for (auto & entity : entityHolder) {
		//Type * downEntity = dynamic_cast<Type*>(entity.get());
		entity->animate (deltaTime);
		entity->updateFromBody ();
		entity->update ();
	}
}

template <class Type, class Identifier>
Type * GameObjectController<Type, Identifier>::operator[](std::size_t index) {
	assert (index < entityHolder.size ());
	return entityHolder[index];
}
