#pragma once
#include <SFML/Graphics.hpp>

/*
	Interface must be in every game, especially in This Game. Yeah, that covers it.
*/

using sf::Mouse;
using sf::RenderWindow;
using sf::Vector2i;

class Interface {
public:
	Interface ();
	virtual ~Interface ();
};

