/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#include "MouseInterface.h"
sf::Vector2i MouseInterface::mousePosition = sf::Vector2i ();
sf::Vector2f MouseInterface::playerOffset = sf::Vector2f ();
float MouseInterface::offsetFactor = 8.f;

void MouseInterface::capturePosition (const sf::RenderWindow & window) {
	mousePosition = sf::Mouse::getPosition (window);
}

void MouseInterface::calculatePlayerOffset (const sf::Vector2f & playerPosition) {
	playerOffset = sf::Vector2f( ((float)mousePosition.x - playerPosition.x) / offsetFactor, 
								 ((float)mousePosition.y - playerPosition.y) / offsetFactor);
}

float MouseInterface::calculateRotation () {
	if (abs (playerOffset.x) < std::numeric_limits<float>::epsilon ())
	{
		if (playerOffset.y <= 0)
			return b2_pi / 2.f;
		else
			return b2_pi * 3.f / 2.f;
	}
	else if (abs (playerOffset.y) < std::numeric_limits<float>::epsilon ()) {
		if (playerOffset.x >= 0)
			return 0;
		else
			return b2_pi;
	}
	else {
		float a = 0;		// y = a*x
		a = playerOffset.y / playerOffset.x;
		float alfa = atan (-a);

		if (playerOffset.x < 0) 
			alfa += b2_pi;

		if (alfa < 0)
			alfa = alfa + 2 * b2_pi;

		return alfa;
	}
}