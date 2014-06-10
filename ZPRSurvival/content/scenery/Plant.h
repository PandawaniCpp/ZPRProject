#pragma once
#include "../../classes/Effectable.h"
#include <SFML/Graphics.hpp>
#include "../../interface/Logger.h"
#include "../../item/ItemController.h"
#define MAX_FOOD 100.f
#define BAR_LENGTH 150.f
/*
	class, which represents Plant obcjct on map
	Plant has amount of food, which can be eaten by creatures
*/
class Plant:
	public Effectable {
public:
	
	/*
	constructor, sets positions, and creating sprite and boxCollision objcet
	*/
	Plant(const sf::Vector2f& positions);
	
	/*
	default destructor
	*/
	virtual ~Plant();
	
	/*
	updates state of plant
	*/
	void update();
	
	/*
	loads static texture for all plants
	*/
	static void loadTexture();
	
	/*
	returns food amount bar, needet for drawing bar over the plant
	*/
	sf::RectangleShape getFoodAmountBar();
	
	/*
		decreases amount of food
	*/
	void isEaten();

	/*
	increases amount of food
	*/
	void addFood();
private:
	
	// amount of food
	float foodAmount;
	//bar which represents amount of food
	sf::RectangleShape foodAmountBar;
	//static texture, used for every plant
	static sf::Texture texture;
	// says how much time something was eaten
	sf::Time lastEatTime;
	// says how much time new fruits was produced
	sf::Time lastAddTime;
	// after eatTime, food can be eaten again
	sf::Time eatTime;
	//after addTime, fruits can be reproduced again
	sf::Time addTime;

	/*
		sets length and color of foodAmountBar
	*/
	void setBar();
};