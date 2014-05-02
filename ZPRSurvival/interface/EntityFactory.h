/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <map>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "ResourcesID.h"
#include "../creature/Creature.h"
#include "../item/Item.h"
#include "../player/Player.h"

/**
	Non-instantiable class for storing all entities prefabs and dynamically creating 
	objects (then returns specific pointer).
*/
class EntityFactory {
public:
	// Container for all prefabs.
	static std::map<Entities::ID, GameObject::Prefab> prefabs;

	// Initialize all prefabs.
	// #TODO make this to load prefab from binary file/-s.
	static void prefabInit ();

	// Creation method for differetn game object types.
	static Creature* createCreature (Entities::ID entityId);
	static Item* createItem (Entities::ID entityId);
	static Player* createPlayer (Entities::ID entityId, sf::Texture & texture, sf::Vector2f position);

private:
	// Special initializaions for prefabs.
	static void playerPrefabsInit ();
	static void creaturePrefabsInit ();
	static void itemPrefabsInit ();
};

