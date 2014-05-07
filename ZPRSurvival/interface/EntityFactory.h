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

	template <class Type>	// Creates entity matching template parameter and arguments.
	static Type * createEntity (Entities::ID entityId, sf::Texture & texture, sf::Vector2f position, sf::Vector2i size);

private:
	// Special initializaions for prefabs.
	static void playerPrefabsInit ();
	static void creaturePrefabsInit ();
	static void itemPrefabsInit ();
};

template <class Type>
Type * EntityFactory::createEntity (Entities::ID entityId, sf::Texture & texture, sf::Vector2f position, sf::Vector2i size) {
	// TEKSTURY ANIMOWANE ZOSTAW PAN W SPOKOJU!!!
	Type * entity = new Type (&prefabs[entityId]);
	texture.setRepeated (prefabs[entityId].isTextureRepeatable);
	entity->setTexture (texture);
	//entity->setTextureRect (sf::IntRect (0, 0, prefabs[entityId].width, prefabs[entityId].height));
	entity->setPosition (position);
	entity->createB2Body (prefabs[entityId]);
	return entity;
}

