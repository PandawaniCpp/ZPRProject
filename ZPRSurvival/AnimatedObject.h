#pragma once
#include "SurvivalObject.h" 

/*
	The String Theory assumes that Player and Creature must be put in the same category,
	but it does not clarify why. Maybe it is the animated texture? Maybe it is the ability
	to move and rotate? Maybe it is the explicit relationship between Animated and Survival
	object? Or maybe it is the inevitable circle of life and death that puts these pure beings 
	on the edge of despair? Or on an island. It depends.
*/

class AnimatedObject : public SurvivalObject {
	public:
	AnimatedObject ();
	virtual ~AnimatedObject ();
};

