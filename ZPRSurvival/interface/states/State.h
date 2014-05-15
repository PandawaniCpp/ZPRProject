/**
	@author	Pawel Kaczynski
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "../ResourcesID.h"

class StateStack;

/**
	Base class for every state.
*/
class State {
public:
	// Unique pointer definition for holding States.
	typedef std::unique_ptr<State> Ptr;
	
	// Parralel data shared between states.
	struct Context {
		// #TODO FILL
	};

	// Constructor.
	State (StateStack& stack, Context context);

	// Default destructor.
	virtual ~State ();

	// Managing the game differently in every state
	virtual void draw () = 0;
	virtual bool update (sf::Time dt) = 0;
	virtual bool handleEvent (const sf::Event& event) = 0;

protected:
	// Allow states to alter the stack from within their own code.
	void requestStackPush (States::ID stateID);
	void requestStackPop ();
	void requestStateClear ();

	// Context getter.
	Context getContext () const;

private:
	// Pointer to StateStack
	StateStack * stateStack;
	
	// Context object (parralel data shared between states).
	Context context;
};

