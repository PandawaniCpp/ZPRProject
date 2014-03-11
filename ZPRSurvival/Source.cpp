#include <SFML/Graphics.hpp>
#include "PerlinNoise.h"

int main() {
	PerlinNoise map;
	sf::RenderWindow window(sf::VideoMode(400, 300), "SFML works!");
	sf::Image im = map.RenderMap(1200, 1200 , 150, 0.5, 255, 255, 255);
	im.saveToFile("Screen.png");
	sf::Texture tx;
	sf::Sprite sprite;

	srand((int)time(NULL));


	tx.create(200, 200);
	tx.loadFromImage(im);
	sprite.setTexture(tx);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}