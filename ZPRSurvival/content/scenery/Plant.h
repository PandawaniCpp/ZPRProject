#pragma once
#include "../../classes/Effectable.h"
#include <SFML/Graphics.hpp>
#include "../../interface/Logger.h"
#include "../../item/ItemController.h"
#define MAX_FOOD 100.f
#define BAR_LENGTH 150.f
class Plant:
	public Effectable {
public:
	Plant(const sf::Vector2f& positions);
	virtual ~Plant();
	void update();
	static void loadTexture();
	sf::RectangleShape getFoodAmountBar();
	void isEaten();
	void addFood();
private:
	float foodAmount;
	sf::RectangleShape foodAmountBar;
	static sf::Texture texture;
	static bool isTexture;
	sf::Time lastEatTime;
	sf::Time lastAddTime;
	sf::Time eatTime;
	sf::Time addTime;
	void setBar();
};