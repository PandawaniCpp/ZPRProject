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
	frameDuration = sf::seconds (0.5f);
	currentAnimation = Textures::P_IDLE;
	animationRepeat = true;

	// Spritesheet for player.
	textureHolder.load (Textures::P_SHEET, "resources/textures/player.png");
	texture = textureHolder.get (Textures::P_SHEET);
	texture.setSmooth (true);
	setTexture (texture);

	// Set sizes for every animation of the player.
	SurvivalObjectView::animationsSize.insert (std::make_pair (Textures::P_IDLE, 10));
	SurvivalObjectView::animationsSize.insert (std::make_pair (Textures::P_WALK, 10));

	// Associate Texture::ID with row number of given .png file.
	textureIdRow.insert (std::make_pair (Textures::P_IDLE, 0));
	textureIdRow.insert (std::make_pair (Textures::P_WALK, 1));

	// Initial texture
	setTextureRect (sf::IntRect (frameNumber*frameSize.x, 0, frameSize.x, frameSize.y));
}

PlayerView::~PlayerView () {
}

void PlayerView::draw (sf::RenderWindow& window) const {
	window.draw(*this);
}
