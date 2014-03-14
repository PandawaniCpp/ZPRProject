#include "MouseInterface.h"

MouseInterface::MouseInterface () {
}

MouseInterface::~MouseInterface () {
}

void MouseInterface::capturePosition (sf::RenderWindow & window, Player * player) {
	sf::Vector2i position = sf::Mouse::getPosition (window);
	player->playerController.setMousePosition (position);
}
