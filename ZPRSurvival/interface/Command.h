/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

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
	Command () : action (), category (Entities::NONE) {};

	Action	action;			// Action performed on GameObject
	Entities::ID category;	// Entity type
};

// Specific action with type downcasting
template <typename Object, typename Function>
Command::Action derivedAction (Function fn)
{
	return [=] (GameObject& node, sf::Time dt) {
		// Check if cast is safe
		assert (dynamic_cast<Object*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn (static_cast<Object&>(node), dt);
	};
}
