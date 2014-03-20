#include "CreatureController.h"


CreatureController::CreatureController() {
	creature = new Creature();
	creatureView = new CreatureView();
}


CreatureController::~CreatureController() {
}

Creature* CreatureController::getCreature() {
	return creature;
}

CreatureView* CreatureController::getCreatureView() {
	return creatureView;
}