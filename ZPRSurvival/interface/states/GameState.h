/**
	@author	Pawel Kaczynski
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "State.h"
#include "../Game.h"

class GameState : public State {
public:
	// Constructor.
	GameState (StateStack & stack, Context context);

	virtual void draw ();
	virtual bool update (sf::Time dt);
	virtual bool handleEvent (const sf::Event& event);

private:
	Game * game;
};

