/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "EntityFactory.h"
std::map<Entities::ID, GameObject::Prefab> EntityFactory::prefabs = std::map<Entities::ID, GameObject::Prefab> ();

void EntityFactory::prefabInit () {
	playerPrefabsInit ();
	creaturePrefabsInit ();
	itemPrefabsInit ();
}

/*Creature * EntityFactory::createCreature (Entities::ID) {

}
*/
Item * EntityFactory::createItem (Entities::ID entityId, sf::Texture & texture, sf::Vector2f position) {
	Item * item = new Item (&prefabs [entityId]);
	texture.setRepeated (prefabs[entityId].isTextureRepeatable);
	item->setTexture (texture);
	item->setTextureRect (sf::IntRect (0, 0, prefabs[entityId].width, prefabs[entityId].height));
	item->setPosition (position);
	item->createB2Body (prefabs[entityId]);
	return item;
}

Player * EntityFactory::createPlayer (Entities::ID entityId, sf::Texture & texture, sf::Vector2f position) {
	Player * player = new Player (&prefabs[entityId]);
	player->setTexture (texture);
	player->setPosition (position);
	player->createB2Body (prefabs[entityId]);
	return player;
}

void EntityFactory::playerPrefabsInit () {
	GameObject::Prefab prefab;
	
	// Entities::PLAYER prefab.
	prefab.width = 50;
	prefab.height = 50;
	prefab.originX = 0.5;
	prefab.originY = 0.5;
	prefab.density = 1.0f;
	prefab.friction = 0.7f;
	prefab.rotation = b2_pi / 2.f;
	prefab.rotationSpeed = 10.f;
	prefab.acceleration = 25.f;
	prefab.linearDamping = 20.f;
	prefab.angularDamping = 2.f;
	prefab.runModifier = 2.f;
	prefab.bodyType = b2_dynamicBody;
	prefab.circleShape = nullptr;
	prefab.isTextureRepeatable = false;
	prefab.polyShape = new b2PolygonShape;
	prefab.polyShape->SetAsBox (prefab.width / 2.0f / GraphicsOptions::pixelPerMeter,
								prefab.height / 2.0f / GraphicsOptions::pixelPerMeter);
	prefab.texture.playerTexture = Textures::P_IDLE;

	prefabs.insert (std::make_pair (Entities::PLAYER, prefab));
}

void EntityFactory::creaturePrefabsInit () {

}

void EntityFactory::itemPrefabsInit () {
	GameObject::Prefab prefab;

	// Entities::WALL prefab.
	prefab.width = 450;
	prefab.height = 100;
	prefab.originX = 0.5;
	prefab.originY = 0.5;
	prefab.density = 1.0f;
	prefab.friction = 0.7f;
	prefab.rotation = 0;
	prefab.rotationSpeed = 0.f;
	prefab.acceleration = 0.f;
	prefab.linearDamping = 1.f;
	prefab.angularDamping = 0.f;
	prefab.runModifier = 0.f;
	prefab.bodyType = b2_staticBody;
	prefab.circleShape = nullptr;
	prefab.isTextureRepeatable = true;
	prefab.polyShape = new b2PolygonShape;
	prefab.polyShape->SetAsBox (prefab.width / 2.0f / GraphicsOptions::pixelPerMeter,
								prefab.height / 2.0f / GraphicsOptions::pixelPerMeter);
	prefab.texture.itemTexture = Textures::I_WALL;

	prefabs.insert (std::make_pair (Entities::WALL, prefab));
}
