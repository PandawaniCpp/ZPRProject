/**
    @date	03.04.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Command.h"
#include "Game.h"
#include "../player/Player.h"

/**
    Non-instantiable class for interpreting particular keys and their combinations. 
*/
class KeyboardInterface {
public:
    // Special keys flags.
    enum SpecialKeys {
        CONTROL = 1,
        SHIFT = 1 << 1,
        ALT = 1 << 2,
        SYSTEM = 1 << 3,
    };

    // Assign keys and actions.
    static void assignKeys ();
    static void assignActions ();

    // Interprets keys based on game state.
    static Command * pressedKeyHandle (States::ID state, sf::Keyboard::Key key);
    static Command * releasedKeyHandle (States::ID state, sf::Keyboard::Key key);

private:
    // Associates action with command to be executed.
    static std::map<std::pair<sf::Keyboard::Key, States::ID>, Commands::ID> pressedKeyBindings;
    static std::map<std::pair<sf::Keyboard::Key, States::ID>, Commands::ID> releasedKeyBindings;

    // Associates key pressed on given state with action to be performed.
    static std::map<Commands::ID, Command> actionBindings;

    // Automatically creates multi-mappings for keys with more than one state.
    static void insertKeyBinding (bool pressed, sf::Keyboard::Key key, int stateFlags, Commands::ID command);
};

