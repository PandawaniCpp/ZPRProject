/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#include "KeyboardInterface.h"

std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> KeyboardInterface::pressedKeyBindings = std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> ();
std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> KeyboardInterface::releasedKeyBindings = std::map<std::pair<sf::Keyboard::Key, GameState::ID>, Commands::ID> ();
std::map<Commands::ID, Command> KeyboardInterface::actionBindings = std::map<Commands::ID, Command> ();

void KeyboardInterface::assignKeys () {
	pressedKeyBindings.insert (std::make_pair (std::make_pair(sf::Keyboard::Escape, GameState::PLAYING), Commands::G_EXIT));
	pressedKeyBindings.insert (std::make_pair (std::make_pair(sf::Keyboard::Escape, GameState::IN_MENU), Commands::G_EXIT));
}

void KeyboardInterface::assignActions () {
	for (unsigned int i = Commands::NONE; i < Commands::COMMANDS_COUNT; ++i)
		actionBindings.insert (std::make_pair (static_cast<Commands::ID>(i), Command ()));

	//actionBindings[Commands::EXIT].action = derivedAction<Game> (GameExit ());
	actionBindings[Commands::G_EXIT].category = Entities::NONE;
	actionBindings[Commands::G_EXIT].commandType = Commands::G_EXIT;
	actionBindings[Commands::MOVE_FORWARD].action = derivedAction<Dynamic>(EntityMover (0.f, -1.f));
}

Command KeyboardInterface::pressedKeyHandle (GameState::ID state, sf::Keyboard::Key key) {
	auto found = pressedKeyBindings.find (std::make_pair (key, state));
	if (found != pressedKeyBindings.end ())
		return actionBindings[found->second];
	else {
		Command command;
		return command;
	}
}

Command KeyboardInterface::releasedKeyHandle (GameState::ID state, sf::Keyboard::Key key) {
	auto found = releasedKeyBindings.find (std::make_pair (key, state));
	if (found != releasedKeyBindings.end ())
		return actionBindings[found->second];
	else {
		Command command;
		return command;
	}
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