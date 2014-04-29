/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "PlayerView.h"

PlayerView::PlayerView () {
	// Set sizes for every animation of the player.
	SurvivalObjectView::frameData.insert (std::make_pair (Textures::P_IDLE, sf::Vector3<int> (50, 50, 10)));
	SurvivalObjectView::frameData.insert (std::make_pair (Textures::P_WALK, sf::Vector3<int> (50, 50, 10)));

	// Current animation parameters
	frameNumber = 0;
	frameDuration = sf::seconds (0.5f);
	currentAnimation = Textures::P_IDLE;
	animationRepeat = true;

	// Load player textures.
	for (unsigned int i = Textures::P_INIT + 1; i < Textures::P_END; ++i) {
		textureHolder.load (static_cast<Textures::ID>(i), "resources/textures/player.png", sf::IntRect(
			0,
			frameData[static_cast<Textures::ID>(i)].y*(i - Textures::P_INIT - 1),
			frameData[static_cast<Textures::ID>(i)].x*frameData[static_cast<Textures::ID>(i)].z,
			frameData[static_cast<Textures::ID>(i)].y));
	}
	setTexture (textureHolder.get (Textures::P_IDLE));

	// Create Box2D body for player.
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2 (this->getPosition().x / GraphicsOptions::pixelPerMeter, 
							   this->getPosition().y / GraphicsOptions::pixelPerMeter);
	bodyDef.type = b2_dynamicBody;
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

PlayerView::~PlayerView () {
}

void PlayerView::draw (sf::RenderWindow& window) const {
	window.draw(*this);
}

void PlayerView::changeTexture () {
	this->setTexture (textureHolder.get (currentAnimation));
}
