/**
    @date	15.05.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
    */

#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "../ResourcesID.h"
#include "../ResourceHolder.h"
#include "../Command.h"

class StateStack;
class Game;

/**
    Base class for every state.
    */
class State {
public:
    // Unique pointer definition for holding States.
    typedef std::unique_ptr<State> Ptr;

    // Constructor.
    State (StateStack& stack, Game * game);

    // Default destructor.
    virtual ~State ();

    // Managing the game differently in every state
    virtual void draw () = 0;
    virtual bool update (sf::Time dt) = 0;
    virtual bool handleEvent (const Command * command) = 0;

    // One time triggered methods: on state becoming active and inactive.
    virtual void onActivate ();
    virtual void onDestroy ();

    // State ID getter.
    States::ID getStateID ();

protected:
    // Allow states to alter the stack from within their own code.
    void requestStackPush (States::ID stateID);
    void requestStackPop ();
    void requestStateClear ();

    // Context getter.
    Game * getGame () const;    // #TODO Used?

    // State's ID. Needed for key mapping interpretation.
    States::ID stateID;

    // Context object (parralel data shared between states).
    Game * game;

private:
    // Pointer to StateStack
    StateStack * stateStack;
};

