/**
    @date	03.04.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#pragma once
#include "../classes/Animated.h"
#include "../classes/Dynamic.h"
#include "../classes/Effectable.h"

/**
    MVC's View for all non-animated (not alive) object in the world.

    \base class: Animated, Dynamic, Effectable
    */
class Item : public Animated<Textures::ITEMS>, public Dynamic, public Effectable {
public:
    // Default constructor.
    Item ();

    // Prefab constructor.
    Item (GameObject::Prefab * prefab);

    // Default destructor.
    virtual ~Item ();

    // Overloaded sf::Sprite draw() method for Item.
    virtual void draw (sf::RenderWindow * window) const;
};

