
//*******************************************************************************
// Class solely for handling the encounter between the creature and player*******

#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Player.h"
#include "Creature.h"
#include "CreatureList.h"


class Encounter
{
public:
	void handleEncounter(Player& player, CreatureList& creatureList);

};


#endif
