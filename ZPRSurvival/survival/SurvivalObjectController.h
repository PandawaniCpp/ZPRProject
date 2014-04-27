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
#include <Box2D/Dynamics/b2World.h>
#define PI 3.14159265		//converting degrees <-> radians

/** 
	MVC's Controller for SurvivalObject class. 
*/
class SurvivalObjectController {
public:
	// Time for one tick. Initialized in Game::run()
	static sf::Time deltaTime;

	// Default constructor.
	SurvivalObjectController ();

	// Default destructor.
	virtual ~SurvivalObjectController ();
};

