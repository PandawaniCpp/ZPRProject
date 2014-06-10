#pragma once
#include "../../classes/GameObject.h"
#include <SFML/Graphics.hpp>

class Plant:
	public GameObject {
public:
	Plant();
	virtual ~Plant();

private:
	int foodAmount;
	sf::Color color;

};

