#include "Plant.h"

bool Plant::isTexture = false;
sf::Texture Plant::texture = sf::Texture();


Plant::Plant(const sf::Vector2f& position) {

	setTexture(texture);

	setPosition(position);
	Prefab prefab;
	prefab.width = 155;
	prefab.height = 135;
	prefab.rotation = 0;
	setOrigin(prefab.width / 2, prefab.height / 2);
	prefab.id = Entities::PLANT;
	prefab.originX = 0.5;
	prefab.originY = 0.5;
	prefab.bodyType = b2_staticBody;
	prefab.polyShape = new b2PolygonShape;
	prefab.polyShape->SetAsBox(prefab.width / 2.0f / GraphicsOptions::pixelPerMeter,
							   prefab.height / 2.0f / GraphicsOptions::pixelPerMeter);

	setColor(sf::Color(255,0,0));
	foodAmount = MAX_FOOD;
	this->createB2Body(prefab);
}

Plant::~Plant() {
}


void Plant::update() {
	if (foodAmount > 0) {
		--foodAmount;
		float colorParameter;
		colorParameter = foodAmount / MAX_FOOD * 255;
		setColor(sf::Color((static_cast<int>(colorParameter)), 0, 0));
	}
}


void Plant::loadTexture() {

	texture.loadFromFile("./content/scenery/bush.png");

}