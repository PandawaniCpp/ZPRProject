/**
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
    // Create entity accordingly to prefab options
    Type * entity = new Type (&prefabs[entityId]);

    // Set info about texture.
    texture.setRepeated (prefabs[entityId].isTextureRepeatable);
    entity->setTextureRect (sf::IntRect (0, 0, size.x, size.y));
    entity->setTexture (texture);
    
    // Place object in the world
    entity->setPosition (position);
    entity->setOrigin (size.x * prefabs[entityId].originX, size.y * prefabs[entityId].originY);

    // Update info about shapes when arguments don't match prefab options
    if (prefabs[entityId].width != size.x || prefabs[entityId].height != size.y) {
        if (prefabs[entityId].polyShape != nullptr) {
            prefabs[entityId].polyShape->SetAsBox (size.x / 2.f / GraphicsOptions::pixelPerMeter,
                                                   size.y / 2.f / GraphicsOptions::pixelPerMeter);
        }
        else if (prefabs[entityId].circleShape != nullptr) {
            // #TODO Fill this
        }
    }

    // Apply physical representation
    entity->createB2Body (prefabs[entityId]);

    return entity;
}

