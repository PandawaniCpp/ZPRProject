/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "GameObject.h"
#define ANGLE_PRECISION 10.0 * DEG_TO_RAD	// Angle precision in radians.
//#define HYPOTENUSE(a,b) sqrt(a*a + b*b)		// Vector length/value (square root of sum of two squared value)

/**
	MVC's View for Dynamic class. Represents objects, that can move, rotate and
	dynamically behave in the game world.

	\base class: GameObject
	\derived:	 Player, Creature, Item
*/
class Dynamic : virtual public GameObject {
public:
	// Flags for describing dynamic object current direction vector.
	enum DIRECTION {
		UP = 1,
		RIGHT = 1 << 1,
		DOWN = 1 << 2,
		LEFT = 1 << 3,
	};

	// Default constructor.
	Dynamic ();

	// Default destructor.
	virtual ~Dynamic ();

	// Update velocity based on direction.
	void update ();

	// Apply direction change
	void applyDirection (int dir);

	// Set rotation to which b2Body should rotate.
	void setTargetRotation (float angle);

	// Whether object should run or not.
	void setRunning (bool isRunning);

protected:
	int direction = 0;		// Combination of Dynamic::DIRECTION flags
	//float maxSpeed;			// Object movement parameters.
	float acceleration;
	float rotationSpeed;	// Object rotation parameters.
	float rotation;
	
	float runModifier;
	bool isAccelerating = false;	// Triggered when current speed is less than maxSpeed
	bool isRotating = false;		// Is object currently rotating.
	bool isRunning = false;
};

// --------------------------------------------------------------------
// Special Dynamic objects commands
// --------------------------------------------------------------------

// Updates info about current movement direction.
// When 'dir' is negative, it means object should not move in this direction anymore.
struct UpdateDirection {
	UpdateDirection (int dir) : direction (dir) {}
	void operator() (Dynamic & object, sf::Time) const {
		object.applyDirection (direction);
	}
	int direction;
};

// Set target rotation to which body should rotate.
struct UpdateRotation {
	UpdateRotation (float angle) : rotation (angle) {}
	void operator() (Dynamic & object, sf::Time) const {
		object.setTargetRotation (rotation);
	}
	float rotation;
};

// Turn running on/off
struct SetRunning {
	SetRunning (bool isRunning) : running (isRunning) {}
	void operator() (Dynamic & object, sf::Time) const {
		object.setRunning (running);
	}
	bool running;
};