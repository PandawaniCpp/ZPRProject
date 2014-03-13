#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PerlinNoise.h"
#include "player/Player.h"
#include "interface/Game.h"
#include "MidpointDisplacementNoise.h"
#include "MapGenerator.h"

int main() {
	/*Game * game;
	game = new Game ();

	game->initialize ();
	game->run();
	game->terminate ();

	delete game;
	*/
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Survive bitch!");

	sf::Texture texture;
	sf::Sprite sprite;
	MidpointDisplacementNoise heightNoise(4096, 4096, 512, true, true, false);
	MidpointDisplacementNoise tempNoise(4096, 4096, 2048, true, true, true);
	MidpointDisplacementNoise forestNoise(4096, 4096, 1024, false, true, false);
	MidpointDisplacementNoise rainNoise(4096, 4096, 1024, false, false, false);

	tempNoise.AddGradient();

	MapGenerator map;
	map.Calculate(heightNoise.GetVector(), tempNoise.GetVector(), rainNoise.GetVector(), forestNoise.GetVector() );
	//heightNoise.GetImage().saveToFile("heightMap.jpg");
	//tempNoise.GetImage().saveToFile("tempMap.jpg");
	//forestNoise.GetImage().saveToFile("forestMap.jpg");
	//rainNoise.GetImage().saveToFile("rainMap.jpg");

	map.GetMap().saveToFile("Test.png");
	texture.loadFromImage( map.GetMap());
	sprite.setTexture(texture);
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}