/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "./../player/Player.h"

/**
	#TODO Class will be probably deleted (not used so far).
*/
class MouseInterface :public Interface {
public:
	MouseInterface ();
	virtual ~MouseInterface ();
	void capturePosition (RenderWindow & window);
	Vector2i getPosition ();

private:
	Vector2i mousePosition;
};

