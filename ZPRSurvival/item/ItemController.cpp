/**
	@date	03.04.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "ItemController.h"

ItemController::ItemController () {
	Item::insertFrameData (Textures::I_WALL, sf::Vector3<int> (450, 100, 1));
	
	// Load item textures
	for (unsigned int i = Textures::I_INIT + 1; i < Textures::I_END; ++i) {		
		textureHolder.load (static_cast<Textures::ITEMS>(i), "resources/textures/items/wall.png", sf::IntRect (
			0,
			Item::frameData[static_cast<Textures::ITEMS>(i)].y*(i - Textures::I_INIT - 1),
			Item::frameData[static_cast<Textures::ITEMS>(i)].x* Item::frameData[static_cast<Textures::ITEMS> (i)].z,
			Item::frameData[static_cast<Textures::ITEMS>(i)].y));
	}
}

ItemController::~ItemController () {

}

