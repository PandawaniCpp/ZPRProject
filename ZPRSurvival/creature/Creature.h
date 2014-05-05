#pragma once
#include "../classes/Animated.h"
#include "../classes/Dynamic.h"
#include "../classes/Effectable.h"


/*
	Dangerous. Fast. Stealthy. Unpredictable. Uncontrollable. None of these words refers to
	what is really happening here. Let's just assume that Creatures live in packs, occAnimatedState::UPy
	specific territory, protect their own existence, often take a walk in the moonligth to
	mutate with another creature and others. And they move. And rotate. And are animated ofc.
*/

class Creature : public Animated<Textures::CREATURES>, public Dynamic, public Effectable {
public:
	Creature ();
	virtual ~Creature ();

};

