/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "PlayerView.h"

PlayerView::PlayerView () {
	textureHolder.load (Textures::P_BASE, "resources/player/player_base.png");
	setTexture (textureHolder.get (Textures::P_BASE));
	texture.setSmooth (true);
}

PlayerView::~PlayerView () {
}

void PlayerView::draw (sf::RenderWindow& window) const {
	window.draw(*this);
}
