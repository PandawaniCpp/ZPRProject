#pragma once
#include "../survival/SurvivalObject.h" 

/*
	The String Theory assumes that Player and Creature must be put in the same category,
	but it does not clarify why. Maybe it is the animated texture? Maybe it is the ability
	to move and rotate? Maybe it is the explicit relationship between Animated and Survival
	object? Or maybe it is the inevitable circle of life and death that puts these pure beings 
	on the edge of despair? Or on an island. It depends.
*/

class AnimatedObject : public SurvivalObject {
public:
	static enum Direction {
		UP = 1, RIGHT = 2, DOWN = 4, LEFT = 8
	};

	AnimatedObject ();
	virtual ~AnimatedObject ();
		//getters
	Vector2<float> getDisplacement ();
	Vector2<float> getSize ();
	float getSpeed ();
	float getRotation ();
	int getDirection ();
		//setters
	void setDisplacement (Vector2<float> displacement);
	void setSize (Vector2<float> size);
	void setSpeed (float revSpeed);
	void setRotation (float rotation);
	void setDirection (int direction);

protected:
	Vector2<float> displacement;	//position change
	Vector2<float> size;
	float speed;
	float rotation;				    //0 degree == north
	int direction;					//combination of AnimatedState::UP, AnimatedState::DOWN, AnimatedState::LEFT and AnimatedState::RIGHT enum flags
};

