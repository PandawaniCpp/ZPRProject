#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../player/Player.h"
#include "../misc/EnumTypes.h"
#include "KeyboardInterface.h"

/*
	Main game class. Responsible for rendering graphics, events handling,
	creating essential game objects, mouse and keyboard controls and 
	initializing as well as finalizing the game itself.
*/

class Game {
public:
	Game ();
	virtual ~Game ();
	void initialize ();
	void run ();
	void terminate ();

private:
	void processEvents ();
	void render ();
	void update ();
	void draw ();
	

private:
	KeyboardInterface * keyboard;
	sf::RenderWindow * gameWindow;

	Player * player;
	gameState state;
};

