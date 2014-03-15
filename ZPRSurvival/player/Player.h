#pragma once
#include "../AnimatedObject.h"
#include "../controller/PlayerController.h"

/*
	The one and only Player class. When Player needs something, it is instantaneously done.
	His faithful squire, named gravely PlayerController, constantly calculate Player's new
	position, rotation, texture and keep track of his inventory, skills, atributes and carry
	his shiny sword. And shield. If he had one.... Maybe his older brother AnimatedObject
	knows something about it. Worth a shot.
*/

using sf::Texture;

class Player : public AnimatedObject {
public:
	Player ();
	virtual ~Player ();
	void setPlayer (void);	//temporary method
	void update ();
	PlayerController playerController;

private:
	void setPlayerTexture ();

private:
	Texture texture;
};

