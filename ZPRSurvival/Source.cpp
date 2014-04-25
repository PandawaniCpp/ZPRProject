#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "./map/PerlinNoise.h"
#include "player/Player.h"
#include "interface/Game.h"
#include "MidpointDisplacementNoise.h"
#include "MapGenerator.h"
#include <cstdio>
int main() {
	Game * game;
	game = new Game ();

	game->initialize ();
	game->run();
	game->terminate ();

	delete game;

}