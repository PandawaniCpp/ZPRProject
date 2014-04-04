#include "PlayerView.h"

PlayerView::PlayerView () {
	textureHolder.load (Textures::P_BASE, "resources/player/player_base.png");
	setTexture (textureHolder.get (Textures::P_BASE));
}

PlayerView::~PlayerView () {
}

void PlayerView::draw (sf::RenderWindow& window) const {
	window.draw(*this);
}
