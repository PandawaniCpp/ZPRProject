/**
    @date	10.06.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "../classes/GameObject.h"

class ContactListener : public b2ContactListener {
public:
    // Default constructor.
    ContactListener ();

    // Default destructor.
    ~ContactListener ();

    void BeginContact (b2Contact* contact);

    void EndContact (b2Contact* contact);

    // Checks for collisions to disable.
    void PreSolve (b2Contact* contact, const b2Manifold* oldManifold);

    void PostSolve (b2Contact* contact, const b2ContactImpulse* impulse);
};

