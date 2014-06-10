/**
    @date	10.06.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "ContactListener.h"

ContactListener::ContactListener () {
}

ContactListener::~ContactListener () {
}

void ContactListener::BeginContact (b2Contact* contact) {

}

void ContactListener::EndContact (b2Contact* contact) {

}

void ContactListener::PreSolve (b2Contact* contact, const b2Manifold* oldManifold) {
    const b2Body* bodyA = contact->GetFixtureA ()->GetBody ();
    const b2Body* bodyB = contact->GetFixtureB ()->GetBody ();
    const GameObject::EntityInfo* infoA = static_cast<GameObject::EntityInfo*>(bodyA->GetUserData ());
    const GameObject::EntityInfo* infoB = static_cast<GameObject::EntityInfo*>(bodyB->GetUserData ());

    if (infoA->type == Entities::VISION_RANGE || infoB->type == Entities::VISION_RANGE)
        contact->SetEnabled (false);
}

void ContactListener::PostSolve (b2Contact* contact, const b2ContactImpulse* impulse) {

}