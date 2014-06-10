/**
	
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
	*/

#include "State.h"
#include "StateStack.h"

State::State (StateStack & stack, Game * game)
: stateStack (&stack), game (game) {
}

State::~State () {
}

States::ID State::getStateID () {
	return stateID;
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

Game * State::getGame () const {
	return game;
}

void State::onActivate () {
}

void State::onDestroy () {
}

