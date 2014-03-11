#include <SFML/Graphics.hpp>
#include "PerlinNoise.h"

int main() {
	PerlinNoise perlin(1200, 700, 150, 0.5, 255, 255, 255, 7);
	sf::RenderWindow window(sf::VideoMode(1200, 700), "SFML works!");
	perlin.RenderTerrainMap();
	sf::Image im = perlin.GetImage();
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