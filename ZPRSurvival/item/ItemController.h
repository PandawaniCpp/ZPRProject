/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../survival/SurvivalObjectController.h"
#include "ItemView.h"
#include "../interface/ResourceHolder.h"

/**
	MVC's Controller for Item class. Hold textures for all views and managed them.

	\base class: SurvivalObjectController
*/
class ItemController : public SurvivalObjectController {
public:
	// Default constructor.
	ItemController ();

	// Default destructor.
	virtual ~ItemController ();

	// Creates new item and return pointer to it. If failed, return nullptr.
	ItemView * ItemController::createItem (Textures::ID textureID, sf::Vector2f position);

	// All items textures.
	ResourceHolder<Texture, Textures::ID> itemTextureHolder;
};

