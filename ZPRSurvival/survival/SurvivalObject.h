#pragma once
#include <SFML/Graphics.hpp>

/*
	SurvivalObject has won "The Most Important Class In The Game" award, in particular circles
	known as TMICITG, but no relation. During the ceremony, one of its rivals (taking its Sprite
	issues into consideration) congratulate the winner with following words: Now you're the thirst.
*/

using sf::Sprite;
using sf::Vector2;

class SurvivalObject {
public:
	SurvivalObject ();
	virtual ~SurvivalObject ();
		//getters
	Vector2<float> getPosition ();
		//setters
	void setPosition (Vector2<float> position);

private:
	Vector2<float> position;		//object position
};

