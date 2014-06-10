/**	
	@date	03.04.2014

	Part of the #TITLE survival game.

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from the use of this software.
*/

#pragma once
#include "GameObject.h"
#include "Effect.h"

/**
	MVC's View for Effectable class. Despite being a GameObject, also stores shader
	effect that can be triggered on demand.
*/
class Effectable : virtual public GameObject {
public:
	// Used to store effects and manage them.
	typedef std::shared_ptr<Effect> EffectPtr;

	// Hold all available effects in the game.
	static std::map <Effects::ID, EffectPtr> effectsHolder;

	// Default constructor.
	explicit Effectable ();

	// Default destructor.
	virtual ~Effectable ();

protected:
	Effect * effect;				// Stores current effect
	Effects::ID currentEffect;		// Current effect ID
};

