/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "PlayerView.h"

PlayerView::PlayerView () {
	// Animation attributes init.
	frameSize.x = frameSize.y = 50;
	frameNumber = 0;
	frameSet = 0;

	// Spritesheet for player.
	textureHolder.load (Textures::P_SHEET, "resources/textures/player.png");
	texture = textureHolder.get (Textures::P_SHEET);
	texture.setSmooth (true);
	setTexture (texture);

	setTextureRect (sf::IntRect (frameNumber*frameSize.x, frameSet*frameSize.y, frameSize.x, frameSize.y));
}

PlayerView::~PlayerView () {
}

void PlayerView::draw (sf::RenderWindow& window) const {
	window.draw(*this);
}
