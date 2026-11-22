#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Creature.h"
#include "CreatureList.h"
#include "Player.h"

class Encounter
{
public:
	void handleEncounter(Player& player, CreatureList& creatureList);
};

#endif
