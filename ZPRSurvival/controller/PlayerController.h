#pragma once
#include "BaseController.h"

/*
	Humble Player's servant. Some say he relies on BaseController's actions, but it is not true.
	He fully imitates them. But it would be rude not to mention his additional skills, such as
	Keyboard and Mouse input processing, ... fair enough. But remember, don't play cat and mouse with him.
*/

class PlayerController : public BaseController {
public:
	PlayerController ();
	virtual ~PlayerController ();
		//data manipulators
	void preparePlayerMove (int direction, bool isPressed);		//keep track of current move phase
	void calculatePlayerRotation ();
	void setPlayerPosition (Vector2<int> position);
	void setMousePosition (Vector2i position);
		//getters
	playerState getState ();
	Vector2<float> getSize ();
	Vector2i getMousePosition ();

private:
	playerState state = IDLE;
	Vector2i mousePosition;
	Vector2<float> size;
};

