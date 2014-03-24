#pragma once
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "../player/PlayerController.h"

using sf::Keyboard;

class KeyboardInterface : public Interface {
public:
	KeyboardInterface ();
	virtual ~KeyboardInterface ();
	int inputHandle (Keyboard::Key key, bool isPressed, int state, PlayerController * playerController);

private:
};

