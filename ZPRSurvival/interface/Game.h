#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "./../player/PlayerController.h"
#include "./../MapGenerator.h"
#include "KeyboardInterface.h"
#include "MouseInterface.h"

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

private:
	// Called in run (). Catch all user generated events and pass them fwd.
	void processEvents ();

	//
	void update (Time deltaTime);
	void render ();
	//other methods
	void draw ();


private:
	Time TIME_PER_FRAME;				//keep the frame duration fixed
	Game::State state;					//describe, in which state the game is in the moment
	RenderWindow * gameWindow;
	PlayerController * playerController;
	KeyboardInterface * keyboard;
	MouseInterface * mouse;
	/*Map * map;
	Creatures * creatures;*/

	MapGenerator * generator;			//-> move to another class (which will be an object here) 
	Sprite mapSprite; //temporary		
	Texture mapTexture; //temporary		-> move somewhere else

	Vector2<float> globalDisplacement;	//all object except player will move by the value of this vector
	FloatRect worldBounds;
	View worldView;
	float scrollSpeed;
	SurvivalObjectView sceneGraph;
	std::array<SurvivalObjectView*, LAYER_COUNT> sceneLayers;

	Font font;
};

