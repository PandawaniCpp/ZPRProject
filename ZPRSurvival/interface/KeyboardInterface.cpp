/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#include "KeyboardInterface.h"

// Static containers initialization
std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> KeyboardInterface::pressedKeyBindings = std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> ();
std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> KeyboardInterface::releasedKeyBindings = std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> ();
std::map<Commands::ID, Command> KeyboardInterface::actionBindings = std::map<Commands::ID, Command> ();

void KeyboardInterface::assignKeys () {
	pressedKeyBindings.insert (std::make_pair (std::make_pair(sf::Keyboard::Escape, GameState::PLAYING), Commands::G_EXIT));
	pressedKeyBindings.insert (std::make_pair (std::make_pair(sf::Keyboard::Escape, GameState::IN_MENU), Commands::G_EXIT));
	pressedKeyBindings.insert (std::make_pair (std::make_pair(sf::Keyboard::F1, GameState::PLAYING), Commands::CON_TRIGGER));
	pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::W, GameState::PLAYING), Commands::MOVE_FORWARD));
	pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::S, GameState::PLAYING), Commands::MOVE_BACKWARD));
	pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::A, GameState::PLAYING), Commands::TURN_LEFT));
	pressedKeyBindings.insert (std::make_pair (std::make_pair (sf::Keyboard::D, GameState::PLAYING), Commands::TURN_RIGHT));
}

void KeyboardInterface::assignActions () {
	// Fill container with empty Commands and assign them types;
	for (unsigned int i = Commands::NONE; i < Commands::COMMANDS_COUNT; ++i) {
		actionBindings.insert (std::make_pair (static_cast<Commands::ID>(i), Command ()));
		actionBindings[static_cast<Commands::ID>(i)].commandType = static_cast<Commands::ID>(i);
	}


	// Assign specific actions to every command;
	actionBindings[Commands::G_EXIT].category = Entities::NONE;
	actionBindings[Commands::CON_TRIGGER].category = Entities::NONE;
	actionBindings[Commands::MOVE_FORWARD].action = derivedAction<Dynamic>(EntityMover (5.f, -5.f));
	actionBindings[Commands::MOVE_FORWARD].category = Entities::PLAYER;
	actionBindings[Commands::MOVE_BACKWARD].action = derivedAction<Dynamic> (EntityMover (-5.f, 5.f));
	actionBindings[Commands::MOVE_BACKWARD].category = Entities::PLAYER;
	actionBindings[Commands::TURN_LEFT].action = derivedAction<Dynamic> (EntityRotate (+0.5f));
	actionBindings[Commands::TURN_LEFT].category = Entities::PLAYER;
	actionBindings[Commands::TURN_RIGHT].action = derivedAction<Dynamic> (EntityRotate(-0.5f));
	actionBindings[Commands::TURN_RIGHT].category = Entities::PLAYER;
}

Command KeyboardInterface::pressedKeyHandle (GameState::ID state, sf::Keyboard::Key key) {
	auto found = pressedKeyBindings.find (std::make_pair (key, state));
	if (found != pressedKeyBindings.end ())
		return actionBindings[found->second];
	else 
		return Command();
}

Command KeyboardInterface::releasedKeyHandle (GameState::ID state, sf::Keyboard::Key key) {
	auto found = releasedKeyBindings.find (std::make_pair (key, state));
	if (found != releasedKeyBindings.end ())
		return actionBindings[found->second];
	else
		return Command();
}

/*KeyboardInterface::KeyboardInterface () {
}

KeyboardInterface::~KeyboardInterface () {
}*/

/*int KeyboardInterface::inputHandle (Keyboard::Key key, int state) {
	if (key == Keyboard::Escape)		//exit the game
		return Game::State::EXIT;			//#TEMP

	switch (state) {						//controls the game state
		case Game::State::IN_MENU:
			if (key == Keyboard::Return)		//#TEMP
				return Game::State::PLAYING;		//pseudo-start of the game
			break;
		case Game::State::PLAYING: {						//all events in the actual game
			game->getPlayerController()->preparePlayerMove (key, Keyboard::isKeyPressed (key));
			return Game::State::PLAYING;
		}
		default: 
			return -1;
	}
	return -1;
}*/