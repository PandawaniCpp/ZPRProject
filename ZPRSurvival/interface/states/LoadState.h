/**
    @date	15.05.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#pragma once
#include "State.h"
#include "../Game.h"
#include "../../classes/Animation.h"

class LoadState : public State {
public:
    // Constructor.
    LoadState (StateStack & stack, Game * game);

    virtual void draw ();
    virtual bool update (sf::Time dt);
    virtual bool handleEvent (const Command * command);

    virtual void onActivate ();
    virtual void onDestroy ();

private:
    void init ();

    sf::Time textEffectTime;
    sf::Text text;
    sf::Thread thread;
    Animation loadingAnimation;
    sf::Sprite loadingDone;
    sf::Texture loadingDoneTexture;
    bool loadingFinished = false;

    std::vector<std::string> loadingTexts;
};

