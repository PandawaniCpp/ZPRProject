/**
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Player.h"

Player::Player () {
    // Current animation parameters
    frameDuration = sf::seconds (0.5f);
    currentAnimation = Textures::P_IDLE;
    animationRepeat = true;
    
    // Dynamic body parameters.
    rotationSpeed = 0.5f;
    acceleration = 10.f;
    runModifier = 2.f;
    
    // Set ID
    entityInfo.type = Entities::PLAYER;

    this->setOrigin (frameData[currentAnimation].x / 2.f, frameData[currentAnimation].y / 2.f);
    this->resetAnimation ();
}

Player::Player (GameObject::Prefab * prefab) {
    // Current animation parameters
    frameDuration = sf::seconds (0.5f);
    currentAnimation = prefab->texture.playerTexture;
    animationRepeat = true;

    // Dynamic body parameters.
    rotationSpeed = prefab->rotationSpeed;
    acceleration = prefab->acceleration;
    runModifier = prefab->runModifier;
    anglePrecision = prefab->rotationSpeed * DEG_TO_RAD;

    // Set ID
    entityInfo.type = prefab->id;	// #TODO NAPRAW !!!!!

    this->setOrigin (prefab->width * prefab->originX, prefab->height * prefab->originY);
    this->resetAnimation ();

    applyVisionRange (Entities::PLANT, 1000);
}

Player::~Player () {
}

void Player::draw (sf::RenderWindow * window) const {
    window->draw (*this);
}