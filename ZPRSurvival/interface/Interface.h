/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#pragma once
#include <SFML/Graphics.hpp>

using sf::Mouse;
using sf::RenderWindow;
using sf::Vector2i;

/**
	Interface must be in every game, especially in This Game. Yeah, that covers it.
*/
class Interface {
public:
	// Default constructor
	Interface ();

	// Default destructor
	virtual ~Interface ();
};

