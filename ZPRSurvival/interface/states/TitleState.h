/**
    @date	15.05.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#pragma once
#include "State.h"
#include "../Game.h"

class TitleState : public State {
public:
    // Constructor.
    TitleState (StateStack & stack, Game * game);

    virtual void draw ();
    virtual bool update (sf::Time dt);
    virtual bool handleEvent (const Command * command);

    virtual void onActivate ();
    virtual void onDestroy ();

private:
    sf::Text text;
    sf::Texture texture;
    sf::Sprite background;
    sf::Time textEffectTime;
    bool textVisible;
    
};

