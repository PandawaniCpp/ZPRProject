/**
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#pragma once
#include "../classes/Animated.h"
#include "../classes/Dynamic.h"
#include "../classes/Effectable.h"

/**
    MVC's View for all animated (alive) object in the world.

    \base class: Animated, Dynamic, Effectable
    */
class Creature : public Animated<Textures::CREATURES>, public Dynamic, public Effectable {
public:
    // Default constructor.
    Creature ();

    // Prefab constructor.
    Creature (GameObject::Prefab * prefab);

    // Default destructor.
    virtual ~Creature ();

    // Overloaded sf::Sprite draw() method for Item.
    virtual void draw (sf::RenderWindow * window) const;
};

/**
    Dangerous. Fast. Stealthy. Unpredictable. Uncontrollable. None of these words refers to
    what is really happening here. Let's just assume that Creatures live in packs, occAnimatedState::UPy
    specific territory, protect their own existence, often take a walk in the moonligth to
    mutate with another creature and others. And they move. And rotate. And are animated ofc.
    */
