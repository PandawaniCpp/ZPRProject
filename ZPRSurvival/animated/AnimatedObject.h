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
	AnimatedObject ();
	virtual ~AnimatedObject ();
		//getters
	Vector2<float> getDisplacement ();
	Vector2<float> getSize ();
	float getMaxFSpeed ();
	float getMaxRSpeed ();
	float getForSpeed ();
	float getRevSpeed ();
	float getRotation ();
	int getDirection ();
	MovingPhase getPhase ();
		//setters
	void setDisplacement (Vector2<float> displacement);
	void setSize (Vector2<float> size);
	void setMaxFSpeed (float maxFSpeed);
	void setMaxRSpeed (float maxRSpeed);
	void setForSpeed (float forSpeed);
	void setRevSpeed (float revSpeed);
	void setRotation (float rotation);
	void setDirection (int direction);
	void setPhase (MovingPhase phase);

protected:
	Vector2<float> displacement;	//position change
	Vector2<float> size;
	float maxFSpeed;				//forward and reverse speed maxes...
	float maxRSpeed;
	float forSpeed;					//...and current values
	float revSpeed;
	float rotation;				    //0 degree == north
	int direction;					//combination of UP, DOWN, LEFT and RIGHT enum flags
	MovingPhase phase;				//ac- or decelerating and which way headed
};

