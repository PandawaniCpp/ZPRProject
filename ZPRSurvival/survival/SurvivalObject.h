/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Graphics.hpp>

/**
	MVC's Model for SurvivalObject class. Base for other Models in whole game.

	\derived: AnimatedObject
*/
class SurvivalObject {
public:
	// Default constructor.
	SurvivalObject ();

	// Default destructor.
	virtual ~SurvivalObject ();

	// Getters

	sf::Vector2<float> getPosition ();
		
	// Setters

	void setPosition (sf::Vector2<float> position);

private:
	sf::Vector2<float> position;		// Object position (in game world).
};

/**
	SurvivalObject has won "The Most Important Class In The Game" award, in particular circles
	known as TMICITG, but no relation. During the ceremony, one of its rivals (taking its Sprite
	issues into consideration) congratulate the winner with following words: Now you're the thirst.
*/

