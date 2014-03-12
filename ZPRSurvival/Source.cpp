#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PerlinNoise.h"
#include "player/Player.h"
#include "interface/Game.h"

int main() {
	Game * game;
	game = new Game ();

	game->initialize ();
	game->run();
	game->terminate ();

	delete game;

	return 0;
}