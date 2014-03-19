#pragma once
#include <SFML/Graphics.hpp>
#include "Interface.h"
#include "./../player/Player.h"

class MouseInterface :public Interface {
public:
	MouseInterface ();
	virtual ~MouseInterface ();
	void capturePosition (RenderWindow & window);
	Vector2i getPosition ();

private:
	Vector2i mousePosition;
};

