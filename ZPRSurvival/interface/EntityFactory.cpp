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

Item * EntityFactory::createItem (Entities::ID) {
}
*/
Player * EntityFactory::createPlayer (Entities::ID entityId, sf::Texture & texture, sf::Vector2f position) {
	Player * player = new Player (prefabs[entityId]);
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
	prefab.maxSpeed = 10.0;
	prefab.rotationSpeed = 4.f;
	prefab.acceleration = 1000.f;
	prefab.bodyType = b2_dynamicBody;
	prefab.circleShape = nullptr;
	prefab.polyShape = new b2PolygonShape;
	prefab.polyShape->SetAsBox (prefab.width / 2.0f / GraphicsOptions::pixelPerMeter,
								prefab.height / 2.0f / GraphicsOptions::pixelPerMeter);

	prefabs.insert (std::make_pair (Entities::PLAYER, prefab));
}

void EntityFactory::creaturePrefabsInit () {

}

void EntityFactory::itemPrefabsInit () {

}
