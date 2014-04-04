/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include <map>
#include <cassert>
#include "../survival/SurvivalObjectView.h"

/** 
	Basically shows transparent layer on top with detailed information about the game.
*/
class Console : public SurvivalObjectView {
public:
	// Holds all parameters to draw: name - value.
	static std::map<std::string, float> params;

	// Default constructor
	Console ();
	
	// Default destructor
	virtual ~Console ();

	// Inserts new pair 'name-value' into Console::params
	void insert (const std::string & name, const float & value);

	// Draw console on the screen with given params
	// \see Console::params
	void draw ();
};

