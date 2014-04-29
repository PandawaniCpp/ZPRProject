/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <map>
#include <memory>
#include <vector>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "../options/GraphicsOptions.h"
#include "../interface/ResourcesID.h"

/**
	MVC's View for SurvivalObject class. Implements scene graph to draw objects with and
	stores current view's texture.

	\base class: sf::Sprite
	\derived: AnimatedObjectView, Console
*/
class SurvivalObjectView : public sf::Sprite {
public:
	// Stores frame count of particular animation (texture).
	// x-param : frame width
	// y-param : frame height
	// z-param : frame count
	static std::map<Textures::ID, sf::Vector3<int>> frameData;	

	// Box2D World
	static b2World boxWorld;

	// Used to create scene nodes.
	// Very often use of this particular unique_ptr.
	typedef std::unique_ptr<SurvivalObjectView> Ptr;		

	// Default constructor.
	SurvivalObjectView ();

	// Default destructor.
	virtual ~SurvivalObjectView ();

	// Overloaded sf::Sprite draw method.
	virtual void draw (sf::RenderWindow& window) const;

	// Draw this object and all children.
	virtual void drawAll (sf::RenderWindow* window) const;

	// Adds child to vector 'children'.
	// Added child has 'parent' set to calling object.
	void attachChild (Ptr & child);

	// Removes node from vector.
	void detachChild (const SurvivalObjectView& node);	//remove child from vector

	// Removes all (if any left) childs.
	void detachAllChilds ();

	// Check if had any childs.
	bool hasChilds ();

	// Animation handling.
	void animate (sf::Time dt);

	// Change animation to draw.
	void changeAnimation (Textures::ID textID);

	// Reset frames and times for next animation.
	void resetAnimation ();

	// Get current aniumation
	Textures::ID getCurrentAnimation ();

	// Move the Box2D body.
	//void moveBody (sf::Vector2<float> moveVector);
	
protected:	
	std::vector<Ptr> children;		// All children to draw after this object is drawn.
	SurvivalObjectView* parent;		// Pointer ro the parent (one level above).

	Textures::ID currentAnimation;		// Animation state.
	sf::Time frameDuration;
	sf::Time elapsedTime;
	int frameNumber;					// Number of frame actually written.
	bool animationRepeat;				// Animation is repeatable.
	//bool animationActive;				// #TODO Check if neccessary

	b2Body * boxBody;					// Box2D Dynamic object.
};

