#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "./../player/Player.h"
#include "./../MapGenerator.h"
#include "./../misc/EnumTypes.h"
#include "KeyboardInterface.h"
#include "MouseInterface.h"

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
		//in the run() function (they are executed all over again as long the gameWindow is open)
	void processEvents ();
	void update (Time deltaTime);
	void render ();
		//other
	void draw ();
	

private:
	Time TIME_PER_FRAME;				//keep the frame duration fixed
	RenderWindow * gameWindow;
	KeyboardInterface * keyboard;
	MouseInterface * mouse;		 
	
	MapGenerator * generator;			//-> move to another class (which will be an object here) 
	Sprite mapSprite; //temporary		
	Texture mapTexture; //temporary		-> move somewhere else
	Player * player;
	gameState state;					//describe, in which state the game is in the moment
	Vector2<float> globalDisplacement;	//all object except player will move by the value of this vector
										//every time the player wants to move.
	Font font;
};

