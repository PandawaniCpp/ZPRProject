/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "ItemController.h"

ItemController::ItemController () {
	Item::insertAnimationData (Textures::I_WALL, sf::Vector3<int> (150, 100, 3));
	//textureHolder.load (Textures::I_WALL, "resources/textures/items/wall.png", sf::IntRect(0,0,150,100));

	// Load item textures
	for (unsigned int i = Textures::I_INIT + 1; i < Textures::I_END; ++i) {		// #TODO INACZEJ !!!!
		textureHolder.load (static_cast<Textures::ITEMS>(i), "resources/textures/items/wall.png", sf::IntRect (
			0,
			Item::frameData[static_cast<Textures::ITEMS>(i)].y*(i - Textures::P_INIT - 1),
			Item::frameData[static_cast<Textures::ITEMS>(i)].x* Item::frameData[static_cast<Textures::ITEMS> (i)].z,
			Item::frameData[static_cast<Textures::ITEMS>(i)].y));
	}
}

ItemController::~ItemController () {

}

void ItemController::createEntity (Entities::ID entityID, Textures::ITEMS itemTexture, sf::Vector2f position) {
	entityHolder.push_back (EntityFactory::createItem (entityID,
							textureHolder.get (itemTexture),
							position));
	entityHolder[entityHolder.size()-1]->animate (deltaTime);
	//Item * newItem;
	//b2BodyType type;
	//switch (textureID) {
	//	case Textures::I_STONE: type = b2_dynamicBody; break;
	//	default: break;
	//}
	//newItem = new Item (textureHolder.get (textureID), type, position);
	////newItem->setPosition (position);

	//return newItem;
}
