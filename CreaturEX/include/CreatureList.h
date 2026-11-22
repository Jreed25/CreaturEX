#ifndef CREATURELIST_H
#define CREATURELIST_H

#include "Creature.h"

#include <vector>

class CreatureList
{
private:
	std::vector<Creature> creatures;

public:
	CreatureList();
	const std::vector<Creature>& getCreatures() const;
	Creature getRandomCreature() const;
	void addCreature(const Creature& newCreature);
};

#endif
