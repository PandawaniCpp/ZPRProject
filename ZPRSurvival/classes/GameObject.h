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
#define RAD_TO_DEG 180.0f / b2_pi

/**
	MVC's View for GameObject class. Implements scene graph to draw objects and provides
	Box2D physics engine functionality

	\base class: sf::Sprite
	\derived: Animated, Effectable, Dynamic, Console, Map
*/
class GameObject : public sf::Sprite {
public:
	// Prefab structure defining all in-game object.
	typedef struct Prefab {
		int width = 1;
		int height = 1;
		float originX = 0;
		float originY = 0;
		float density = 0;
		float friction = 0;
		b2BodyType bodyType = b2_dynamicBody;
		b2PolygonShape * polyShape = nullptr;		// ONLY ONE shape can and should be
		b2CircleShape * circleShape = nullptr;		// nullptr at a time.
	};

	// Used to create scene nodes.
	typedef std::shared_ptr<GameObject> Ptr;

	// Box2D World
	static b2World boxWorld;

	// Default constructor.
	GameObject ();

	// Default destructor.
	virtual ~GameObject ();

	// Overloaded sf::Sprite draw method.
	virtual void draw (sf::RenderWindow& window) const;

	// Draw this object and all children.
	virtual void drawAll (sf::RenderWindow* window) const;

	// Get updated position and rotation from b2Body and apply it to Sprite.
	void updateFromBody ();

	// Adds child to vector 'children'.
	// Added child has 'parent' set to calling object.
	void attachChild (Ptr & child);

	// Removes node from vector.
	void detachChild (const GameObject& node);	//remove child from vector

	// Removes all (if any left) childs.
	void detachAllChilds ();

	// Check if had any childs.
	bool hasChilds ();

	// Create b2Body 
	void createB2Body (Prefab prefab);
	
protected:	
	std::vector<Ptr> children;		// All children to draw after this object is drawn.
	GameObject* parent;			// Pointer ro the parent (one level above).
	b2Body * boxBody;					// Box2D Dynamic object.
};

/**
	GameObject has won "The Most Important Class In The Game" award, in particular circles
	known as TMICITG, but no relation. During the ceremony, one of its rivals (taking its Sprite
	issues into consideration) congratulate the winner with following words: Now you're the thirst.
*/

