#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../interface/EnumTypes.h"
#include "../animated/AnimatedObject.h"
#include <sstream>
#define PI 3.14159265		//converting degrees <-> radians

/*
	Practically the (demi)god of all living beings. It's endless posibilities include fames
	such as: FLAWLESS positioning, EPIC rotation, EXTRAORDINARY object acceleation, PIXEL
	PER PIXEL collisions, FAIRLY GOOD two dimensional texture animation and MUCH MORE....
	HOLY MISSISIPI!!!
*/

using sf::Vector2;
using sf::Time;
using sf::Vector2i;
using sf::Keyboard;
using sf::RenderWindow;

class BaseController {
public:
	BaseController ();
	//BaseController (BaseController & baseController);	//copy constructor
	virtual ~BaseController ();
		//object manipulators
	void prepareMove (int & direction, MovingPhase & phase);
	void calculateMove (AnimatedObject * animatedObject);
	void calculateRotation (float & rotation, const Vector2<float> & rotationVector);
	void move (const int direction, Vector2<float> & position, const Vector2<float> & displacement);											//changes position of the object relatively
	/*void rotate (float angle);								//rotate relatively*/
	void setDeltaTime (Time deltaTime);

protected:
	Time deltaTime;					//time for one tick

private:
};

