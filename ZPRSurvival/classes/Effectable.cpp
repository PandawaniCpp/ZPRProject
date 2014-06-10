/**	
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Effectable.h"

Effectable::Effectable () {
}

Effectable::~Effectable () {
}

void Effectable::applyVisionRange (const Entities::ID target, const unsigned int range) {
    Prefab prefab;
    prefab.bodyType = b2_staticBody;
    prefab.id = Entities::VISION_RANGE;
    prefab.circleShape = new b2CircleShape;
    prefab.circleShape->m_radius = range / GraphicsOptions::pixelPerMeter;
   
    createB2Body (prefab);
}