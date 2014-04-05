/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "../survival/SurvivalObjectView.h"

/**
	MVC's View for AnimatedObject class. Responsible for drawing animated objects on the screen.

	\ base class: SurvivalObjectView
	\ derived:    PlayerView, CreatureView
*/
class AnimatedObjectView : public SurvivalObjectView {
public:
	// Default constructor.
	AnimatedObjectView ();

	// Default destructor.
	virtual ~AnimatedObjectView ();
};

