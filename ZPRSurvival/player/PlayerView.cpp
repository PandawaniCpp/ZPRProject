#include "PlayerView.h"

PlayerView::PlayerView () {
	texture.loadFromFile ("resources/player.png");
	setTexture (texture);
}

PlayerView::~PlayerView () {
}
