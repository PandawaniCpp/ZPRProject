/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#include "SurvivalObjectView.h"

std::map<Textures::ID, int> SurvivalObjectView::animationsSize = std::map<Textures::ID, int> ();

SurvivalObjectView::SurvivalObjectView () {
}

SurvivalObjectView::~SurvivalObjectView () {
	detachAllChilds ();
}

void SurvivalObjectView::attachChild (Ptr & child)
{
	child->parent = this;		// Caller is parent for attached child.
	children.push_back (std::move (child));		// Insert new child.
}

void SurvivalObjectView::detachChild (const SurvivalObjectView& node)
{
	// Lambda-expression search for child; return true if found.
	auto found = std::find_if (children.begin (), children.end (), [&] (Ptr& p) -> bool { return p.get () == &node; });
	assert (found != children.end ());
	Ptr result = std::move (*found);		// Assign child pointer to 'result'.
	result->parent = nullptr;				// Erase parent.
	result.reset();
	children.erase (found);					// Erase child.
}

void SurvivalObjectView::detachAllChilds () {
	for (unsigned i = 0; i < children.size (); ++i) {
		if (children[i]->hasChilds ())
			children[i]->detachAllChilds ();
		detachChild (*children[i]);
	}
}

void SurvivalObjectView::draw (sf::RenderWindow& window) const {
	window.draw (*this);
}

void SurvivalObjectView::drawAll (sf::RenderWindow* window) const {
	// Draw myself.
	this->draw (*window);

	// Draw all children.
	for (const Ptr& child : children) {
		child->drawAll (window);
	}
}

bool SurvivalObjectView::hasChilds () {
	if (children.size () == 0)
		return false;
	else
		return true;
}

void SurvivalObjectView::animate (sf::Time dt, int row) {
	// #TODO COMMENTS!!!!!!!!!!!
	sf::Time timePerFrame = frameDuration / static_cast<float>(animationsSize[currentAnimation]);
	elapsedTime += dt;
	sf::Vector2i textureBounds (this->getTexture ()->getSize ());
	sf::IntRect textureRect = this->getTextureRect ();

	if (frameNumber == 0)
		textureRect = sf::IntRect (0, row*frameSize.y, frameSize.x, frameSize.y);
	while (elapsedTime >= timePerFrame && (frameNumber <= animationsSize[currentAnimation] || animationRepeat)) {
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
			textureRect.left = 0;
		elapsedTime -= timePerFrame;
		if (animationRepeat) {
			frameNumber = (frameNumber + 1) % animationsSize[currentAnimation];
			if (frameNumber == 0)
				textureRect = sf::IntRect (0, row*frameSize.y, frameSize.x, frameSize.y);
		}
		else {
			frameNumber++;
		}
	}
	this->setTextureRect (textureRect);
}

void SurvivalObjectView::changeAnimation (Textures::ID textID) {
	currentAnimation = textID;
}

void SurvivalObjectView::resetAnimation () {
	elapsedTime = sf::Time::Zero;
	frameNumber = 0;
}

Textures::ID SurvivalObjectView::getCurrentAnimation () {
	return currentAnimation;
}