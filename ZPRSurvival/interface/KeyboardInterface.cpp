/**
    @date	03.04.2014

    Part of the #TITLE survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "KeyboardInterface.h"

// Static containers initialization
std::map<std::pair<sf::Keyboard::Key, States::ID>, Commands::ID> KeyboardInterface::pressedKeyBindings = std::map<std::pair<sf::Keyboard::Key, States::ID>, Commands::ID> ();
std::map<std::pair<sf::Keyboard::Key, States::ID>, Commands::ID> KeyboardInterface::releasedKeyBindings = std::map<std::pair<sf::Keyboard::Key, States::ID>, Commands::ID> ();
std::map<Commands::ID, Command> KeyboardInterface::actionBindings = std::map<Commands::ID, Command> ();

void KeyboardInterface::assignKeys () {
    insertKeyBinding (true, sf::Keyboard::F1, States::MENU | States::GAME | States::PAUSE, Commands::CON_TRIGGER);
    insertKeyBinding (true, sf::Keyboard::Return, States::MENU | States::TITLE | States::LOAD, Commands::PRESS_ANY_KEY);
    
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::Escape, States::GAME), Commands::G_PAUSE));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::Return, States::PAUSE), Commands::G_RESUME));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::Escape, States::PAUSE), Commands::G_EXIT));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::Period, States::GAME), Commands::RES_UP));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::Comma, States::GAME), Commands::RES_DOWN));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::F, States::GAME), Commands::SET_FULLSCREEN));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::M, States::GAME), Commands::SAVE_MAP_TO_IMG));

    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::W, States::GAME), Commands::MOVE_FORWARD));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::S, States::GAME), Commands::MOVE_BACKWARD));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::A, States::GAME), Commands::MOVE_LEFT));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::D, States::GAME), Commands::MOVE_RIGHT));
    pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::LShift, States::GAME), Commands::START_RUN));

    releasedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::W, States::GAME), Commands::STOP_FORWARD));
    releasedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::S, States::GAME), Commands::STOP_BACKWARD));
    releasedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::A, States::GAME), Commands::STOP_LEFT));
    releasedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::D, States::GAME), Commands::STOP_RIGHT));
    releasedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::LShift, States::GAME), Commands::STOP_RUN));
}

void KeyboardInterface::assignActions () {
    // Fill container with empty Commands and assign them types;
    for (unsigned int i = Commands::NONE; i < Commands::COMMANDS_COUNT; ++i) {
        actionBindings.insert (std::make_pair (static_cast<Commands::ID>(i), Command ()));
        actionBindings[static_cast<Commands::ID>(i)].commandType = static_cast<Commands::ID>(i);
    }

    // Assign specific actions to every command;
    actionBindings[Commands::RES_UP].specialKeys = SpecialKeys::CONTROL;
    actionBindings[Commands::RES_DOWN].specialKeys = SpecialKeys::CONTROL;
    actionBindings[Commands::SET_FULLSCREEN].specialKeys = SpecialKeys::CONTROL;
    actionBindings[Commands::SAVE_MAP_TO_IMG].specialKeys = SpecialKeys::CONTROL + SpecialKeys::SHIFT;

    actionBindings[Commands::MOVE_FORWARD].action = derivedAction<Dynamic> (UpdateDirection (Dynamic::UP));
    actionBindings[Commands::MOVE_FORWARD].category = Entities::PLAYER;
    actionBindings[Commands::MOVE_BACKWARD].action = derivedAction<Dynamic> (UpdateDirection (Dynamic::DOWN));
    actionBindings[Commands::MOVE_BACKWARD].category = Entities::PLAYER;
    actionBindings[Commands::MOVE_LEFT].action = derivedAction<Dynamic> (UpdateDirection (Dynamic::LEFT));
    actionBindings[Commands::MOVE_LEFT].category = Entities::PLAYER;
    actionBindings[Commands::MOVE_RIGHT].action = derivedAction<Dynamic> (UpdateDirection (Dynamic::RIGHT));
    actionBindings[Commands::MOVE_RIGHT].category = Entities::PLAYER;
    actionBindings[Commands::START_RUN].action = derivedAction<Dynamic> (SetRunning (true));
    actionBindings[Commands::START_RUN].category = Entities::PLAYER;

    actionBindings[Commands::STOP_FORWARD].action = derivedAction<Dynamic> (UpdateDirection (-Dynamic::UP));
    actionBindings[Commands::STOP_FORWARD].category = Entities::PLAYER;
    actionBindings[Commands::STOP_BACKWARD].action = derivedAction<Dynamic> (UpdateDirection (-Dynamic::DOWN));
    actionBindings[Commands::STOP_BACKWARD].category = Entities::PLAYER;
    actionBindings[Commands::STOP_LEFT].action = derivedAction<Dynamic> (UpdateDirection (-Dynamic::LEFT));
    actionBindings[Commands::STOP_LEFT].category = Entities::PLAYER;
    actionBindings[Commands::STOP_RIGHT].action = derivedAction<Dynamic> (UpdateDirection (-Dynamic::RIGHT));
    actionBindings[Commands::STOP_RIGHT].category = Entities::PLAYER;
    actionBindings[Commands::STOP_RUN].action = derivedAction<Dynamic> (SetRunning (false));
    actionBindings[Commands::STOP_RUN].category = Entities::PLAYER;
}

Command * KeyboardInterface::pressedKeyHandle (States::ID state, sf::Keyboard::Key key) {
    auto found = pressedKeyBindings.find (std::make_pair (key, state));
    if (found != pressedKeyBindings.end ())
        return &actionBindings[found->second];
    else 
        return new Command();   //  #TODO RETURN Commands::NONE command instead of this
}

Command * KeyboardInterface::releasedKeyHandle (States::ID state, sf::Keyboard::Key key) {
    auto found = releasedKeyBindings.find (std::make_pair (key, state));
    if (found != releasedKeyBindings.end ())
        return &actionBindings[found->second];
    else
        return new Command();   //  #TODO RETURN Commands::NONE command instead of this
}

void KeyboardInterface::insertKeyBinding (bool pressed, sf::Keyboard::Key key, int stateFlags, Commands::ID command) {
    for (int i = States::NONE + 1; i < States::LIMIT; i *= 2) {
        bool flagExist = stateFlags & i;
        if (flagExist) {
            if (pressed)
                pressedKeyBindings.insert (std::make_pair (std::make_pair (key, static_cast<States::ID>(i)), command));
            else
                releasedKeyBindings.insert (std::make_pair (std::make_pair (key, static_cast<States::ID>(i)), command));
        }
    }
}