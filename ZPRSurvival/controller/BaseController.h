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
	void prepareMove (int direction, bool isPressed);	//keep track of current move phase
	void calculateMove ();								//calculate speed vector based on phase
	void move ();				//changes position oj the object
	void rotate (double newAngle);
	void setDeltaTime (sf::Time deltaTime);
		//getters
	Vector2<double> getPosition ();
	double getRotation ();
	int getDirection ();

protected:
	double maxFSpeed;
	double maxRSpeed;
	Vector2<double> position;		//object position
	Vector2<double> displacement;	//position change
	double rotation;				//0 degree == north
	double forSpeed;
	double revSpeed;
	int direction;
	movingPhase phase;
	sf::Time deltaTime;

private:
};

