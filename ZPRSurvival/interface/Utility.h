/**
    @date	15.05.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <Box2D/Box2D.h>

void centerOrigin (sf::Sprite& sprite);

void centerOrigin (sf::Text& text);

float calculateRotationToTarget (sf::Vector2f source, sf::Vector2f target);