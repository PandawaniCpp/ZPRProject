/**
	@date	15.05.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
	*/

#include "Utility.h"

void centerOrigin (sf::Sprite& sprite) {
	sf::FloatRect bounds = sprite.getLocalBounds ();
	sprite.setOrigin (std::floor (bounds.width / 2.f), std::floor (bounds.height / 2.f));
}

void centerOrigin (sf::Text& text) {
	sf::FloatRect bounds = text.getLocalBounds ();
	text.setOrigin (std::floor (bounds.width / 2.f), std::floor (bounds.height / 2.f));
}
