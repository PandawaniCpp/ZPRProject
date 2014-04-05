/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#define PI 3.14159265		//converting degrees <-> radians

class SurvivalObjectController {
public:
	SurvivalObjectController ();
	virtual ~SurvivalObjectController ();

	// Updates deltaTime by given parameter.
	void setDeltaTime (sf::Time deltaTime);

protected:
	sf::Time deltaTime;					//time for one tick
};

