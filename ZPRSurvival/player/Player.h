#pragma once
#include "../AnimatedObject.h"
#include "../controller/PlayerController.h"

using sf::Texture;
using sf::Sprite;

class Player : public AnimatedObject {
private:
	PlayerController playerController;
	Texture texture;

public:
	Player ();
	virtual ~Player ();
	void SetPlayer (void);
};

