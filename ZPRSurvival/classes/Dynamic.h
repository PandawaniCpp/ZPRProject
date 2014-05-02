/**
	@author	Pawel Kaczynski
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "GameObject.h"

/**
	MVC's View for Dynamic class. Represents objects, that can move, rotate and
	dynamically behave in the game world.

	\base class: GameObject
	\derived:	 Player, Creature, Item
*/
class Dynamic : virtual public GameObject {
public:
	// Default constructor.
	Dynamic ();

	// Default destructor.
	virtual ~Dynamic ();
};

