#pragma once
#include <SFML/Graphics.hpp>
#include "../misc/EnumTypes.h"

using sf::Vector2;

class BaseController {
public:
	BaseController ();
	BaseController (BaseController & baseController);	//copy constructor
	virtual ~BaseController ();
		//object manipulators
	void prepareMove (int direction, bool isPressed);
	void move ();	//changes position oj the object
	void rotate (double newAngle);
		//getters
	Vector2<double> getPosition ();
	double getRotation ();

protected:
	Vector2<double> position;		//object position
	Vector2<double> displacement;	//position change
	double rotation;				//0 degree == north
	double speed;
	int direction;

private:
};

