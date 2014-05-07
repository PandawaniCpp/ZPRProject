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

void GameObject::attachChild (ObjectPtr child)
{
	child->parent = this;		// Caller is parent for attached child.
	children.push_back (std::move (child));		// Insert new child.
}

void GameObject::detachChild (const GameObject& node)
{
	// Lambda-expression search for child; return true if found.
	auto found = std::find_if (children.begin (), children.end (), [&] (ObjectPtr& p) -> bool { return p.get () == &node; });
	assert (found != children.end ());
	ObjectPtr result = std::move (*found);		// Assign child pointer to 'result'.
	result->parent = nullptr;				// Erase parent.
	children.erase (found);					// Erase child.
}

void GameObject::detachAllChilds () {
	for (unsigned i = 0; i < children.size (); ++i) {
		if (children[i]->hasChilds ())
			children[i]->detachAllChilds ();
		detachChild (*children[i]);
	}
}

void GameObject::draw (sf::RenderWindow* window) const {
	window->draw (*this);
}

void GameObject::drawAll (sf::RenderWindow* window) const {
	// Draw myself.
	this->draw (window);

	// Draw all children.
	for (const ObjectPtr& child : children) {
		child->drawAll (window);
	}
}

void GameObject::passCommand (Command * command, sf::Time dt) {
	if (command->category == this->entityId)
		command->action (*this, dt);
	else
		for (const ObjectPtr& child : children) {
			child->passCommand (command, dt);
	}
}

void GameObject::updateFromBody () {
	this->setPosition (boxBody->GetPosition ().x * GraphicsOptions::pixelPerMeter,
					   boxBody->GetPosition ().y * GraphicsOptions::pixelPerMeter);

	this->setRotation (360.f - boxBody->GetAngle () * RAD_TO_DEG);
}
bool GameObject::hasChilds () {
	if (children.size () == 0)
		return false;
	else
		return true;
}

void GameObject::createB2Body (Prefab prefab) {
	// Create Box2D body for player.
	b2BodyDef bodyDef;		// Body definitions

	// Position == Sprite's origin
	bodyDef.position = b2Vec2 (this->getPosition ().x / GraphicsOptions::pixelPerMeter,
							   this->getPosition ().y / GraphicsOptions::pixelPerMeter);

	bodyDef.type = prefab.bodyType;		// Dynamic, static or kinetic.
	boxBody = boxWorld.CreateBody (&bodyDef);	// B2Body creation and assigment.
	boxBody->SetTransform (boxBody->GetPosition (), prefab.rotation);
	boxBody->SetAngularDamping (prefab.angularDamping);
	boxBody->SetLinearDamping (prefab.linearDamping);

	// Fixture definition.
	b2FixtureDef fixtureDef;
	fixtureDef.density = prefab.density;
	fixtureDef.friction = prefab.friction;
		
	if (prefab.polyShape == nullptr)		// Chooses from available prefab's shape.
		fixtureDef.shape = (b2Shape*)prefab.circleShape;
	else
		fixtureDef.shape = (b2Shape*)prefab.polyShape;

	// Fixture creation
	boxBody->CreateFixture (&fixtureDef);
}

b2Body * GameObject::getBody () {
	return boxBody;
}