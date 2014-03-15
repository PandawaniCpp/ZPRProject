#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../misc/EnumTypes.h"
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

class BaseController {
public:
	BaseController ();
	BaseController (BaseController & baseController);	//copy constructor
	virtual ~BaseController ();
		//object manipulators
	void prepareMove (int direction);						//set new direction for object to move
	void calculateMove ();									//calculate speed vector based on phase
	void calculateRotation (Vector2<float> destination);	//rotates object to point to given destination
	void move ();											//changes position of the object relatively
	void setPosition (Vector2<float> position);				//set new position
	void rotate (float angle);								//rotate relatively
	void setRotation (float rotation);						//set new rotation
	void setDeltaTime (Time deltaTime);
		//getters
	Vector2<float> getPosition ();
	Vector2<float> getDisplacement ();
	float getRotation ();
	float getFSpeed ();
	float getRSpeed ();
	int getDirection ();
	int getPhase ();

protected:
	Vector2<float> position;		//object position
	Vector2<float> displacement;	//position change
	float maxFSpeed;				//forward and reverse speed maxes...
	float maxRSpeed;
	float forSpeed;					//...and current values
	float revSpeed;
	float rotation;				    //0 degree == north
	int direction;					//combination of UP, DOWN, LEFT and RIGHT enum flags
	movingPhase phase;				//ac- or decelerating and which way headed
	Time deltaTime;					//time for one tick

private:
};

