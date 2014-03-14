#pragma once
#include "BaseController.h"

class PlayerController : public BaseController {
public:
	PlayerController ();
	virtual ~PlayerController ();
		//data manipulators
	void setPlayerPosition (Vector2<double> position);
	void setMousePosition (sf::Vector2i position);
	void calculateRotation ();
		//getters
	playerState getState ();
	Vector2<float> getSize ();
	sf::Vector2i getMousePosition ();

private:
	playerState state = IDLE;
	sf::Vector2i mousePosition;
	Vector2<float> size;
};

