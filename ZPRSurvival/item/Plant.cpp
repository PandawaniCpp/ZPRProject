#include "Plant.h"

sf::Texture Plant::texture = sf::Texture();


Plant::Plant(const sf::Vector2f& position) {

	eatTime = sf::seconds(2.5f);
	addTime = sf::seconds(0.2f);
	lastEatTime = sf::seconds(0.f) ;
	lastAddTime = sf::seconds(0.f);
	setTexture(texture);
	Prefab prefab;
	setPosition(position);
	prefab.originX = 0.5;
	prefab.originY = 0.5;
	prefab.width = 155;
	prefab.height = 135;
	prefab.rotation = 0;
	setOrigin(prefab.width / 2, prefab.height / 2);
	prefab.id = Entities::PLANT;
	prefab.bodyType = b2_staticBody;
	prefab.polyShape = new b2PolygonShape;
	prefab.polyShape->SetAsBox(prefab.width / 2.0f / GraphicsOptions::pixelPerMeter,
							   prefab.height / 2.0f / GraphicsOptions::pixelPerMeter);

	foodAmount = MAX_FOOD;
	this->createB2Body(prefab);
	foodAmountBar.setPosition(position.x - prefab.width / 2, position.y - 20 - prefab.height / 2);
	foodAmountBar.setSize(sf::Vector2f(155, 10));

}

Plant::~Plant() {
}




void Plant::update() {
	lastEatTime+=ItemController::deltaTime;
	lastAddTime+=ItemController::deltaTime;
	if (lastAddTime > addTime) {
		lastAddTime = sf::seconds(0.f);
		addFood();
	}
}

sf::RectangleShape Plant::getFoodAmountBar() {
	return foodAmountBar;
}


void Plant::loadTexture() {
	texture.loadFromFile("./resources/textures/items/bush.png");
}

void Plant::isEaten() {
	if (lastEatTime > eatTime) {
		lastEatTime = sf::seconds(0.f);
		foodAmount -= 40;
		if (foodAmount < 0) {
			foodAmount = 0;
		}
		setBar();
	}
}

void Plant::addFood() {
	foodAmount ++;
	if (foodAmount > MAX_FOOD) {
		foodAmount = MAX_FOOD;
	}
	setBar();
}

void Plant::setBar() {
	float colorParameter;
	colorParameter = foodAmount / MAX_FOOD;
	foodAmountBar.setFillColor(sf::Color((255 - static_cast<int>(colorParameter * 255)), (static_cast<int>(colorParameter * 255)), 0));
	foodAmountBar.setSize(sf::Vector2f(static_cast<int>(colorParameter * 155), 10));
}