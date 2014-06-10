/**    
    @date	03.04.2014

    Part of the Vege Zombies survival game.

    This software is provided 'as-is', without any express or implied warranty.
    In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "GameObject.h"
#include "../interface/Utility.h"

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
    explicit Dynamic ();

    // Default destructor.
    virtual ~Dynamic ();

    // Take b2Body transform and change its rotation instantly.
    void rotateInstantly ();

    // Continously rotate entity until desired rotation is reached.
    void rotateEntity ();

    // Continously move entity to reach destined point.
    void moveToPoint ();

    // Set force vector to the center of the mass (based on direction and rotation)
    void applyForce ();

    // Apply direction change
    void applyDirection (int dir);

    // Setters

    void setTargetRotation (float rotation);
    void setRunning (bool isRunning);
    void setDestination (const sf::Vector2f destination);
    void setIsFollowing (const bool isFollowing);

    // Getters

    bool getIsRunning ();
    int getDirection ();
    bool getIsFollowing ();

protected:
    int direction = 0;		// Combination of Dynamic::DIRECTION flags
    float acceleration;
    float rotationSpeed;	// Object rotation parameters.
    float rotation;         // Rotation to which b2Body should rotate.
    sf::Vector2f destination;
    
    float runModifier;
    float anglePrecision;
    bool isAccelerating = false;	// Triggered when current speed is less than maxSpeed
    bool isRotating = false;		// Is object currently rotating.
    bool isRunning = false;         // Whether object should run or not.
    bool isFollowing = false;
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