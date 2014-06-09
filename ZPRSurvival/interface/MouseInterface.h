/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#pragma once
#include <climits>
#include <SFML/Graphics.hpp>
#include "./../player/Player.h"
#include "Utility.h"

/**
	Non-instantiable class for interpreting mouse position and keys.
*/
class MouseInterface {
public:
	// Mouse position in window (!) coordinates.
	static sf::Vector2i mousePosition;

	// Player position offset depending on distance between mouse and player.
	static sf::Vector2f playerOffset;

	// Capture mouse position and store it.
	static void capturePosition (const sf::RenderWindow & window);

	// Player offset for dynamic sf::View arrangement.
	static void calculatePlayerOffset (const sf::Vector2f & playerPosition);

	// Calculate rotation based on entity-player dependency.
	static float calculateRotation ();

private:
	static float offsetFactor;			// Player offset factor.
};

