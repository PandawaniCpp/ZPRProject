/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../survival/SurvivalObject.h" 

/**
	MVC's Model for AnimatedObject class. It represents all objects	that move, live and interact. 
	Don't misinterpret the word 'Animated', meaning 'not lifeless'. Holds the state of an object.

	\ base class: SurvivalObject
	\ derived:    Player, Creature
*/
class AnimatedObject : public SurvivalObject {
public:
	// Represents in which way the object is moving relatively to viewing angle.
	enum Direction {
		UP = 1, RIGHT = 2, DOWN = 4, LEFT = 8
	};

	// Default constructor.
	AnimatedObject ();

	// Default destructor
	virtual ~AnimatedObject ();

	// Getters

	sf::Vector2<float> getDisplacement ();
	sf::Vector2<float> getSize ();
	float getSpeed ();
	float getRotation ();
	int getDirection ();

	// Setters

	void setDisplacement (sf::Vector2<float> displacement);
	void setSize (sf::Vector2<float> size);
	void setSpeed (float revSpeed);
	void setRotation (float rotation);
	void setDirection (int direction);

protected:
	sf::Vector2<float> displacement;	// Position change (scaled accordingly to the time frame).
	sf::Vector2<float> size;			// Width and height.
	float speed;					// Moving speed (in px)
	float rotation;				    // Which way headed (0 degree == 'north').
	int direction;					// Combination of UP, DOWN, LEFT and RIGHT enum flags, see: AnimatedObject::Direction.
};


/**
	The String Theory assumes that Player and Creature must be put in the same category,
	but it does not clarify why. Maybe it is the animated texture? Maybe it is the ability
	to move and rotate? Maybe it is the explicit relationship between Animated and Survival
	object? Or maybe it is the inevitable circle of life and death that puts these pure beings
	on the edge of despair? Or on an island. It depends.
*/