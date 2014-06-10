/**
    @date	15.05.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#include "Utility.h"

void centerOrigin (sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds ();
    sprite.setOrigin (std::floor (bounds.width / 2.f), std::floor (bounds.height / 2.f));
}

void centerOrigin (sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds ();
    text.setOrigin (std::floor (bounds.width / 2.f), std::floor (bounds.height / 2.f));
}

float calculateRotationToTarget (sf::Vector2f source, sf::Vector2f target) {
    sf::Vector2f offset = target - source;


    if (abs (offset.x) < std::numeric_limits<float>::epsilon ()) {
        if (offset.y <= 0)
            return b2_pi / 2.f;
        else
            return b2_pi * 3.f / 2.f;
    }
    else if (abs (offset.y) < std::numeric_limits<float>::epsilon ()) {
        if (offset.x >= 0)
            return 0;
        else
            return b2_pi;
    }
    else {
        float a = 0;		// y = a*x
        a = offset.y / offset.x;
        float alfa = atan (-a);

        if (offset.x < 0)
            alfa += b2_pi;

        if (alfa < 0)
            alfa = alfa + 2 * b2_pi;

        return alfa;
    }
}
