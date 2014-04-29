/**
	@author	Pawel Kaczynski, Kacper Domanski, Andrzej Siadkowski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "./map/PerlinNoise.h"
#include "player/Player.h"
#include "interface/Game.h"
#include "interface/Logger.h"
#include "MidpointDisplacementNoise.h"
#include "MapGenerator.h"

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