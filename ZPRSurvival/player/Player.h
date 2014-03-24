#pragma once
#include "../animated/AnimatedObject.h"

/*
	The one and only Player class. When Player needs something, it is instantaneously done.
	His faithful squire, named gravely PlayerController, constantly calculate Player's new
	position, rotation, texture and keep track of his inventory, skills, atributes and carry
	his shiny sword. And shield. If he had one.... Maybe his older brother AnimatedObject
	knows something about it. Worth a shot.
*/

class Player : public AnimatedObject {
public:
	static enum State {
		IDLE = 0, MOVING, USING_ITEM, CRAFTING,
	};

	Player ();
	virtual ~Player ();
		//getter
	Player::State getState ();
		//setters
	void setState (Player::State state);

private:
	Player::State state = Player::IDLE;
};

