#pragma once
#include "../AnimatedObject.h"
#include "../controller/PlayerController.h"

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
	sf::Texture texture;
};

