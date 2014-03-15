#pragma once
#include <SFML/Graphics.hpp>

/*
	SurvivalObject has won "The Most Important Class In The Game" award, in particular circles
	known as TMICITG, but no relation. During the ceremony, one of its rivals (taking its Sprite
	issues into consideration) congratulate the winner with following words: Now you're the thirst.
*/

using sf::Sprite;

class SurvivalObject : public Sprite {
	public:
	SurvivalObject ();
	virtual ~SurvivalObject ();
};

