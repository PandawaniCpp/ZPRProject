#pragma once
#include <SFML/Graphics.hpp>
using sf::Vector2;

class BaseController {
	private:
	Vector2<double> position;		//object position
	double viewAngle;				//0 degree == north

	public:
	BaseController ();
	BaseController (BaseController & baseController);	//copy constructor
	virtual ~BaseController ();
	
	void Move (Vector2<double> positionDelta);	//changes position oj the object
	void Rotate (double newAngle);	

};

