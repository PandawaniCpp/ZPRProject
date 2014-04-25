#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "./../player/PlayerController.h"
#include "KeyboardInterface.h"
#include "MouseInterface.h"
#include "./../map/WorldMapView.h"
#include "./../Logger.h"
#include <sstream>

/*
	Main game class. Responsible for rendering graphics, events handling,
	creating essential game objects, mouse and keyboard controls and 
	initializing as well as finalizing the game itself.
*/

using namespace sf;
using namespace std;

class Game {
public:
	static enum State {
		UNKNOWN = 0, INIT, IN_MENU, PLAYING, PAUSE, EXIT
	};

	Game ();
	virtual ~Game ();
	void initialize ();
	void run ();
	void terminate ();

private:
		//in the run() function (they are executed all over again as long the gameWindow is open)
	void processEvents ();
	void update (Time deltaTime);
	void render ();
		//other
	void draw ();
	

private:
	Time TIME_PER_FRAME;				//keep the frame duration fixed
	RenderWindow * gameWindow;
	PlayerController * playerController;
	KeyboardInterface * keyboard;
	MouseInterface * mouse;		 

	
	WorldMapView * worldMap;			//-> move to another class (which will be an object here) 
	
	Game::State state;					//describe, in which state the game is in the moment
	Vector2<float> globalDisplacement;	//all object except player will move by the value of this vector
										//every time the player wants to move.
	FloatRect worldBounds;
	View worldView;
							
	Font font;

};

