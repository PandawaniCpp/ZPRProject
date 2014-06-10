/**
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "CreatureController.h"

CreatureController::CreatureController () {
    Creature::insertFrameData (Textures::C_ZOMBIE, sf::Vector3<int> (150, 150, 8));

    // Load item textures
    for (unsigned int i = Textures::C_INIT + 1; i < Textures::C_END; ++i) {		        // #TODO INACZEJ !!!!
        textureHolder.load (static_cast<Textures::CREATURES>(i), "resources/textures/creatures/zombie.png", sf::IntRect (
            0,
            Creature::frameData[static_cast<Textures::CREATURES>(i)].y*(i - Textures::C_INIT - 1),
            Creature::frameData[static_cast<Textures::CREATURES>(i)].x* Creature::frameData[static_cast<Textures::CREATURES> (i)].z,
            Creature::frameData[static_cast<Textures::CREATURES>(i)].y));
    }
}

CreatureController::~CreatureController () {

}

void CreatureController::update (sf::Vector2f playerPosition) {
    this->playerPosition = playerPosition;
    
    // #TEMP
    entityHolder[0]->setDestination (playerPosition);
    entityHolder[0]->setIsFollowing (true);
    entityHolder[0]->moveToPoint ();
    // ------

    //controlStates ();
    //controlEffects ();
    updateEntities ();
}
