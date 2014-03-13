#pragma once
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "../misc/EnumTypes.h"
#include "../controller/BaseController.h"
#include "../player/Player.h"

class KeyboardInterface : public Interface {
public:
	KeyboardInterface ();
	virtual ~KeyboardInterface ();
	int inputHandle (sf::Keyboard::Key key, bool isPressed, int state, Player * player);

private:
	bool movingEnable = false;	
};

