#pragma once
#include "../../classes/Effectable.h"
#include <SFML/Graphics.hpp>
#include "../../interface/Logger.h"
#define MAX_FOOD 100.f
#define BAR_LENGTH 150.f
class Plant:
	public Effectable {
public:
	Plant(const sf::Vector2f& positions);
	virtual ~Plant();
	void update();
	static void loadTexture();
private:
	float foodAmount;
	static sf::Texture texture;
	static bool isTexture;
};