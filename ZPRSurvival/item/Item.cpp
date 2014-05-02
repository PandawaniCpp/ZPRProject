/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "Item.h"

Item::Item () {
}

Item::Item (sf::Texture & texture, b2BodyType type, sf::Vector2f position) {
	this->setTexture (texture);
	this->setPosition (position);
	this->setOrigin (this->getLocalBounds ().width/2, this->getLocalBounds ().height/2);
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2 (position.x / GraphicsOptions::pixelPerMeter,
							   position.y / GraphicsOptions::pixelPerMeter);
	bodyDef.type = type;
	boxBody = boxWorld.CreateBody (&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox (
		this->getGlobalBounds ().width / 2 / GraphicsOptions::pixelPerMeter,
		this->getGlobalBounds ().height / 2 / GraphicsOptions::pixelPerMeter);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &shape;
	boxBody->CreateFixture (&fixtureDef);
}

Item::~Item () {
}

void Item::draw (sf::RenderWindow& window) const {
	window.draw (*this);
}