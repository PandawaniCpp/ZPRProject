/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../classes/GameObjectController.h"
#include "Item.h"
#include "../interface/ResourceHolder.h"

/**
	MVC's Controller for Item class. Hold textures for all views and managed them.

	\base class: SurvivalObjectController
*/
class ItemController : public GameObjectController<Item, Textures::ITEMS> {
public:
	// Default constructor.
	ItemController ();

	// Default destructor.
	virtual ~ItemController ();

	// Creates entity with EntityFactory
	void createEntity (Entities::ID entityID, Textures::ITEMS itemTexture, sf::Vector2f position);
};

