/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "../player/PlayerController.h"

using sf::Keyboard;

/**
	Interprets particular keys and their combinations. 
	#TODO This class will probably be deleted (not used at all)
*/
class KeyboardInterface : public Interface {
public:
	// Special keys flags.
	enum SpecialKeys {
		CONTROL = 1,
		SHIFT = 2,
		ALT = 4,
		SYSTEM = 8
	};
	// Default constructor
	KeyboardInterface ();

	// Default destructor
	virtual ~KeyboardInterface ();

	// #TEMP
	//int inputHandle (Keyboard::Key key, int state);

private:
};

