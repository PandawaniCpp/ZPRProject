#pragma once
#include "../animated/AnimatedObjectController.h"
#include "Creature.h"
#include "CreatureView.h"
class CreatureController:
	public AnimatedObjectController {
public:
	CreatureController();
	virtual ~CreatureController();

	Creature* getCreature();
	CreatureView* getCreatureView();
private:
	Creature* creature;
	CreatureView* creatureView;
};

