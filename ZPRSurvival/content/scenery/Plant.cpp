#include "Plant.h"


Plant::Plant() {
	sf::Image img;

	img.create(20, 20, sf::Color::Black);
	//img.loadFromFile("./plant.png");
	
	if (!img.loadFromFile("./content/scenery/plant.png")) {
		Logger::getInstance() << "Mamy problem kolego" << std::endl;
	}

	texture.create(20, 20);
	texture.loadFromImage(img);
	setTexture(texture);
	//setColor(sf::Color(255,0,0));
	foodAmount = MAX_FOOD;

	//Logger::getInstance() << "tworze planta na srodku"<< std::endl;
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
