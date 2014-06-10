/**
    @date	03.04.2014
  
    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Item.h"

Item::Item () {
}

Item::Item (GameObject::Prefab * prefab) {
    // Current animation parameters
    frameDuration = sf::seconds (0.5f);
    currentAnimation = prefab->texture.itemTexture;
    animationRepeat = true;

    // Dynamic body parameters.
    rotationSpeed = prefab->rotationSpeed;
    acceleration = prefab->acceleration;
    runModifier = prefab->runModifier;
    anglePrecision = rotationSpeed / 2.0 * DEG_TO_RAD;

    this->resetAnimation ();
}

Item::~Item () {
}

void Item::draw (sf::RenderWindow * window) const {
    window->draw (*this);
}