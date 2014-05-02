/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Command.h"

/**
	Non-instantiable class for interpreting particular keys and their combinations. 
*/
class KeyboardInterface {
	//friend class Game;
public:
	// Special keys flags.
	enum SpecialKeys {
		CONTROL = 1,
		SHIFT = 1 << 1,
		ALT = 1 << 2,
		SYSTEM = 1 << 3,
	};

	// Assign keys.
	static void assignKeys ();

	// Interprets keys based on game state.
	static Command pressedKeyHandle (GameState::ID state, sf::Keyboard::Key key);
	static Command releasedKeyHandle (GameState::ID state, sf::Keyboard::Key key);

private:
	// Associates action with command to be executed.
	static std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> pressedKeyBindings;
	static std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> releasedKeyBindings;

	// Associates key pressed on given state with action to be performed.
	static std::map<Commands::ID, Command> actionBindings;
};

