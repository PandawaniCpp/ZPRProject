/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "./../player/PlayerController.h"
#include "./../MapGenerator.h"

/**
	Main game class. Responsible for rendering graphics, events handling,
	creating essential game objects, mouse and keyboard controls and
	initializing as well as finalizing the game itself.
*/
class Game {
public:
	// Represents phase of the game.
	static enum State {
		UNKNOWN = 0, INIT, IN_MENU, PLAYING, PAUSE, EXIT, STATE_COUNT
	};

	// Game layers defining drawing order.
	static enum Layer {
		BACKGROUND, GROUND, LAYER_COUNT
	};

	// Default constructor.
	// Create all default game objects, set game state
	Game ();

	// Default destructor.
	virtual ~Game ();

	// Initial configuration (size, position, scroll speed, map etc.)
	void initialize ();

	// Continuously controlling every input and output (as long as gameWindow is open).
	// Take care of static time frame.
	// \see processEvents(), update() and render()
	void run ();

	// Objects deallocation, saving data etc.
	void terminate ();

	PlayerController * getPlayerController ();

private:
	// Called in run (). Catch all user generated events and pass them forward.
	void processEvents ();

	// Interprets keys actions depending on state.
	// \param  key - key pressed/released
	void keyboardInput (sf::Keyboard::Key key);

	// Check mouse position nad clicks.
	void mouseInput ();

	// Updates frame duration, add responses to player and creatures based on events.
	// Moves the gameView
	// \param  timePerFrame - see Game::timePerFrame
	void update (Time timePerFrame);

	// Draw the whole gameScene on the screen.
	void render ();

	// #TEMP
	void draw ();


private:
	// Main game objects
	RenderWindow * gameWindow;			// Main window for displaying the game.
	PlayerController * playerController;	// MVC's controller of the player.
	View worldView;				// Represents part of the world shown to the player.

	// Game parameters
	Time timePerFrame;			// Keep the frame duration fixed.
	Game::State state;				// Describe, in which state the game is in the moment.
	FloatRect worldBounds;				// World size (in px).
	float scrollSpeed;				// Speed of gameView movement (mostly player's speed).
	SurvivalObjectView sceneGraph;		// Tree with scene nodes put in render order.
	std::array<SurvivalObjectView*, LAYER_COUNT> sceneLayers;		// Different render levels (starting from the bottom).
	Vector2<int> mousePosition;			// Mouse position
	Font font;			// Main game font

	// #TEMP
	MapGenerator * generator;			//-> move to another class (which will be an object here) 
	Sprite mapSprite; //temporary		
	Texture mapTexture; //temporary		-> move somewhere else

	// #TEMP
	Vector2<float> globalDisplacement;	//all object except player will move by the value of this vector
};

