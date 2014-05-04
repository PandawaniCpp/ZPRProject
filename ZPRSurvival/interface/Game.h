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
#include "../player/PlayerController.h"
#include "../map/WorldMapView.h"
#include "../options/GraphicsOptions.h"
#include "../item/ItemController.h"
#include "Console.h"
#include "KeyboardInterface.h"
#include "MouseInterface.h"
#include "CommandQueue.h"

/**
	Main game class. Responsible for rendering graphics, events handling,
	creating essential game objects, mouse and keyboard controls and
	initializing as well as finalizing the game itself.
*/

using namespace std;

class Game {
public:
	// Game title.
	static std::string TITLE;

	// Game layers defining drawing order.
	enum Layer {
		MAP, ITEMS, PLAYER, LIGHTS, CONSOLE, LAYER_COUNT
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

			//PlayerController * getPlayerController ();

private:
	// Initialize controller with entities from factory.
	void entitiesInit ();

	// Initialize layers with default objects.
	void layersInit ();

	// Initialize objects with default values.
	void objectsInit ();

	// Apply options with default values (first call) or when options state changes.
	void applyOptions ();

	// Called in run (). Catch all user generated events and pass them forward.
	void processEvents ();

	// Interprets commands and pass them into scene graph if necessary.
	void commandInterpret ();

	// Execute commands for Game and interface.
	void gameCommandExecute (Command * command);

	// Interprets keys actions depending on state.
	// \param  key - key pressed/released
	void keyboardInput (const sf::Event event);

	// Check mouse position nad clicks.
	void mouseInput ();

	// Updates frame duration, add responses to player and creatures based on events.
	// Moves the gameView
	void update ();

	// Draw the whole gameScene on the screen.
	void render ();

	// #TEMP
	void draw ();

	// Attach new GameObject to given layer.
	void attachChild (GameObject::Ptr * shPtr, Game::Layer layer);

	// Graphics options triggers.
	void setFullscreenEnabled (bool enabled);		// Fullscreen on/off

private:
	// Main game objects
	sf::RenderWindow * gameWindow;			// Main window for displaying the game.
	PlayerController playerController;	// MVC's controller of the player.
	ItemController itemController;
	sf::View worldView;				// Represents part of the world shown to the player.
	Console * console;		// Displays info about player position, object count, memory etc.
	WorldMapView * worldMap;
	CommandQueue commandQueue;
	GameObject sceneGraph;		// Tree with scene nodes put in render order.

	// Game parameters
	std::array<GameObject*, LAYER_COUNT> sceneLayers;		// Different render levels (starting from the bottom).
	sf::Time timePerFrame;			// Keep the frame duration fixed.
	GameState::ID state;				// Describe, in which state the game is in the moment.
	sf::FloatRect worldBounds;			// World size (in px).
	//Vector2f mousePosition;			// Mouse position
	ResourceHolder<sf::Font, Fonts::ID> fontHolder;		//Keep all game's fonts. Pass them lower if necessary.

	// Additional variables
	sf::Vector2f worldViewPosition;			// Top-left corner of the sf::View in global coordinates.
};

