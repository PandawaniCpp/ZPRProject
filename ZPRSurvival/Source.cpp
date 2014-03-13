#include <SFML/Graphics.hpp>
#include "MapGenerator.h"
#include "MidpointDisplacementNoise.h"


int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(512, 512), "Survive, bitch!");
	MidpointDisplacementNoise mid(4096, 4096, 512);
	MapGenerator mapGen;
	mapGen.Calculate(mid.GetImage());
	sf::Image img = mapGen.GetMap();

	
	img.saveToFile("Screen.png");
	sf::Texture text;

	sf::Sprite spr;

	text.create(512, 512);
	text.loadFromImage(img);
	spr.setTexture(text);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(spr);
		window.display();
	}

	return 0;
}