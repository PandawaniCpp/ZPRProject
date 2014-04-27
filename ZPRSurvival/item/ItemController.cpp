/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "ItemController.h"

ItemController::ItemController () {
	itemTextureHolder.load (Textures::I_STONE, "resources/textures/background/groundx.png", sf::IntRect(0,0,300,300));
}

ItemController::~ItemController () {
}

ItemView * ItemController::createItem (Textures::ID textureID, sf::Vector2f position) {
	ItemView * newItem;
	b2BodyType type;
	switch (textureID) {
		case Textures::I_STONE: type = b2_dynamicBody; break;
		default: break;
	}
	newItem = new ItemView (itemTextureHolder.get (textureID), type, position);
	//newItem->setPosition (position);

	return newItem;
}
