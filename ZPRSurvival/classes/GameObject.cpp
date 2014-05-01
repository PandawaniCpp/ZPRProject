/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "GameObject.h"
b2World GameObject::boxWorld = b2World (b2Vec2 (0.0f, 0.0f));

GameObject::GameObject () {
}

GameObject::~GameObject () {
	detachAllChilds ();
}

void GameObject::attachChild (Ptr & child)
{
	child->parent = this;		// Caller is parent for attached child.
	children.push_back (std::move (child));		// Insert new child.
}

void GameObject::detachChild (const GameObject& node)
{
	// Lambda-expression search for child; return true if found.
	auto found = std::find_if (children.begin (), children.end (), [&] (Ptr& p) -> bool { return p.get () == &node; });
	assert (found != children.end ());
	Ptr result = std::move (*found);		// Assign child pointer to 'result'.
	result->parent = nullptr;				// Erase parent.
	result.reset();
	children.erase (found);					// Erase child.
}

void GameObject::detachAllChilds () {
	for (unsigned i = 0; i < children.size (); ++i) {
		if (children[i]->hasChilds ())
			children[i]->detachAllChilds ();
		detachChild (*children[i]);
	}
}

void GameObject::draw (sf::RenderWindow& window) const {
	window.draw (*this);
}

void GameObject::updateFromBody () {
	//boxBody->SetLinearVelocity (b2Vec2 (100.0, 100.0));
	this->setPosition (boxBody->GetPosition ().x * GraphicsOptions::pixelPerMeter,
					   boxBody->GetPosition ().y * GraphicsOptions::pixelPerMeter);

	//this->setRotation (boxBody->GetAngle () * RAD_TO_DEG);
	this->setRotation (this->getRotation () + 1);
}

void GameObject::drawAll (sf::RenderWindow* window) const {
	// Draw myself.
	this->draw (*window);

	// Draw all children.
	for (const Ptr& child : children) {
		child->drawAll (window);
	}
}

bool GameObject::hasChilds () {
	if (children.size () == 0)
		return false;
	else
		return true;
}

void GameObject::createB2Body (b2BodyType bodyType) {
	// Create Box2D body for player.
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2 (this->getPosition ().x / GraphicsOptions::pixelPerMeter,
							   this->getPosition ().y / GraphicsOptions::pixelPerMeter);
	bodyDef.type = bodyType;
	boxBody = boxWorld.CreateBody (&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox (
		this->getLocalBounds ().width / 2 / GraphicsOptions::pixelPerMeter,
		this->getLocalBounds ().height / 2 / GraphicsOptions::pixelPerMeter);
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.7f;
	fixtureDef.shape = &shape;
	boxBody->CreateFixture (&fixtureDef);
}