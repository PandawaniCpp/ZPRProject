/**
	@date	03.04.2014

	Part of the Vege Zombies survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>
#include "ResourcesID.h"

class GameObject;

struct Command {
	// Action to be triggered on specified game object.
	typedef std::function<void (GameObject&, sf::Time)> Action;

	// Default constructor
	Command () : action (), category (Entities::NONE), commandType (Commands::NONE), specialKeys (0) {};

	Action	action;				// Action performed on GameObject. If command considers Game itself, action is 
								// empty and command is only passing type for further recognition.
	Entities::ID category;		// Entity type
	Commands::ID commandType;	// Type of action
	int specialKeys;
};

// Specific action with type downcasting
template <typename Object, typename Function>
Command::Action derivedAction (Function fn)
{
	return [=] (GameObject& node, sf::Time dt) {
		// Check if cast is safe
		assert (dynamic_cast<Object*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn (dynamic_cast<Object&>(node), dt);
	};
}