/**
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#pragma once
#include "../classes/GameObjectController.h"
#include "Creature.h"
#include "../interface/ResourceHolder.h"

/**
    MVC's Controller for Creature class. Hold textures for all views and managed them.

    \base class: SurvivalObjectController
    */
class CreatureController : public GameObjectController<Creature, Textures::CREATURES> {
public:
    // Default constructor.
    CreatureController ();

    // Default destructor.
    virtual ~CreatureController ();
};