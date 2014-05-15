/**
	@author	Pawel Kaczynski
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "StateStack.h"

StateStack::~StateStack () {
}


StateStack::StateStack (State::Context context)
: stateStack () , pendingList (), context (context), factories () {
}

void StateStack::update (sf::Time dt)
{
	// Iterate from top to bottom, stop as soon as update() returns false
	for (auto itr = stateStack.rbegin (); itr != stateStack.rend (); ++itr) {
		if (!(*itr)->update (dt))
			break;
	}

	applyPendingChanges ();
}

void StateStack::draw ()
{
	// Draw all active states from bottom to top
	for (State::Ptr & state : stateStack)
		state->draw ();
}

void StateStack::handleEvent (const sf::Event& event)
{
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for (auto itr = stateStack.rbegin (); itr != stateStack.rend (); ++itr) {
		if (!(*itr)->handleEvent (event))
			break;
	}

	applyPendingChanges ();
}

void StateStack::pushState (States::ID stateID)
{
	pendingList.push_back (PendingChange (PUSH, stateID));
}

void StateStack::popState ()
{
	pendingList.push_back (PendingChange (POP));
}

void StateStack::clearStates ()
{
	pendingList.push_back (PendingChange (CLEAR));
}

bool StateStack::isEmpty () const
{
	return stateStack.empty ();
}

State::Ptr StateStack::createState (States::ID stateID)
{
	auto found = factories.find (stateID);
	assert (found != mFactories.end ());

	return found->second ();
}

void StateStack::applyPendingChanges ()
{
	for (PendingChange change : pendingList)
	{
		switch (change.action) {
			case PUSH:
				stateStack.push_back (createState (change.stateID));
				stateStack.back ()->onActivate ();
				break;

			case POP:
				stateStack.back ()->onDestroy ();
				stateStack.pop_back ();

				if (!stateStack.empty ())
					stateStack.back ()->onActivate ();
				break;

			case CLEAR:
				for (State::Ptr & state : stateStack)
					state->onDestroy ();

				stateStack.clear ();
				break;
		}
	}

	pendingList.clear ();
}

StateStack::PendingChange::PendingChange (Action action, States::ID stateID)
: action (action) , stateID (stateID) {
}

