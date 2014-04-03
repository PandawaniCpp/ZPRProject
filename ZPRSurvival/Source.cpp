/**
	@author	Pawel Kaczynski, Kacper Domanski, Andrzej Siadkowski
	@date	03.04.2014

	Part of the #TITLE survival game.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PerlinNoise.h"
#include "player/Player.h"
#include "interface/Game.h"
#include "MidpointDisplacementNoise.h"
#include "MapGenerator.h"
#include <cstdio>

/**
	Mainly the game main function.
*/
int main() {
	Game * game;
	game = new Game ();

	game->initialize ();
	game->run();
	game->terminate ();

	delete game;

	return 0;
}