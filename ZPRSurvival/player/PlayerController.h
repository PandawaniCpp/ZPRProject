#pragma once
#include "../animated/AnimatedObjectController.h"
#include "Player.h"
#include "PlayerView.h"

/*
	Humble Player's servant. Some say he relies on AnimatedObjectController's actions, but it is not true.
	He fully imitates them. But it would be rude not to mention his additional skills, such as
	Keyboard and Mouse input processing, ... fair enough. But remember, don't play cat and mouse with him.
*/

class PlayerController: public AnimatedObjectController {
public:
	PlayerController ();
	virtual ~PlayerController ();
	void setPlayer ();
	void update (Vector2i mousePosition);
	void render ();
	//void draw (RenderWindow * gameWindow);
		//data manipulators
	void preparePlayerMove (const Keyboard::Key key, const bool isPressed); 	//keep track of current move phase
	void calculatePlayerMove ();
	void calculatePlayerRotation (Vector2i mousePosition);
	void setPosition (Vector2<float> position);	

	Player * getPlayer ();
	PlayerView * getPlayerView ();

private:
	Player * player;
	PlayerView * playerView;
};

