/**
	@date	15.05.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <cassert>
#include "State.h"
#include "../ResourcesID.h"
#include "../KeyboardInterface.h"

class State;

/**
	Class container for holding and managing states in the game.
*/
class StateStack : private sf::NonCopyable {
public:
	// All available actions.
	enum Action {
		PUSH,
		POP,
		CLEAR,
	};

	// Constructor.
	explicit StateStack (Game * game);

	// Default destructor.
	virtual ~StateStack ();
	
	template <typename T>	// Initialize all available states in the game.
	void registerState (States::ID stateID);

	// Managing the game differently in every state
	void update (sf::Time dt);
	void draw ();
	void handleEvent (const Command * command);

	// Insert new state that is currently in effect.
	void pushState (States::ID stateID);

	// Release last used state.
	void popState ();

	// Release all states.
	void clearStates ();

	// Check if no state is currently in effect.
	bool isEmpty () const;

	// Get the ID of the latest state on the stack.
	States::ID getCurrentStateID ();

	// Wait for right moment to apply any changes.
	// Prevents the game from switching a state in the middle of executing some commands.
	void applyPendingChanges ();

private:
	// Creates new State andd allocate approptiate resources.
	State::Ptr createState (States::ID stateID);

	// Package used to change state.
	struct PendingChange {
		explicit PendingChange (Action action, States::ID stateID = States::NONE);
		Action action;
		States::ID stateID;
	};

	// std::vector representing state stack itself.
	std::vector<State::Ptr> stateStack;

	// List if all pending operations on the stack.
	std::vector<PendingChange> pendingList;

	// Parralel data shared between states.
	Game * game;
	
	// Maps state IDs to factory functions.
	std::map<States::ID, std::function<State::Ptr ()> > factories;
};

template <typename T>
void StateStack::registerState (States::ID stateID)
{
	factories[stateID] = [this] () {
		return State::Ptr (new T (*this, game));
	};
}

