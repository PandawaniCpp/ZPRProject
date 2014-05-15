/**
	@author	Pawel Kaczynski
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
	*/

#include "State.h"
#include "StateStack.h"

State::State (StateStack & stack, Context context)
: stateStack (&stack), context (context) {
}

State::~State () {
}

State::Context::Context (Game * game)
: game (game) {
}

void State::requestStackPush (States::ID stateID) {
	stateStack->pushState (stateID);
}

void State::requestStackPop () {
	stateStack->popState ();
}

void State::requestStateClear () {
	stateStack->clearStates ();
}

State::Context State::getContext () const {
	return context;
}

void State::onActivate () {
}

void State::onDestroy () {
}

