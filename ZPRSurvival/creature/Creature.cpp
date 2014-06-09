/**
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Creature.h"

Creature::Creature () {
}

Creature::Creature (GameObject::Prefab * prefab) {
    // Current animation parameters
    frameDuration = sf::seconds (0.7f);
    currentAnimation = prefab->texture.creatureTexture;
    animationRepeat = true;

    // Dynamic body parameters.
    rotationSpeed = prefab->rotationSpeed;
    acceleration = prefab->acceleration;
    runModifier = prefab->runModifier;
    anglePrecision = prefab->rotationSpeed * DEG_TO_RAD;

    // Set ID
    entityInfo.type = prefab->id;

    this->setOrigin (prefab->width * prefab->originX, prefab->height * prefab->originY);
    this->resetAnimation ();
}

Creature::~Creature () {
}

void Creature::draw (sf::RenderWindow * window) const {
    window->draw (*this);
}