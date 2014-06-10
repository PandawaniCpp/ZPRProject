#pragma once
#include "../../classes/GameObject.h"
#include <SFML/Graphics.hpp>
#include "../../interface/Logger.h"
#define MAX_FOOD 100.f

class Plant:
	public GameObject {
public:
	Plant();
	virtual ~Plant();
	void update();
private:
	float foodAmount;
	sf::Texture texture;

};

