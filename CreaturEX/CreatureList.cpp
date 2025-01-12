// Implementation file for Creature List

#include "CreatureList.h"
#include <vector>

CreatureList::CreatureList()
{
	creatures.push_back(Creature("Cloopar", 20, 5, 25, 5.6, 100, 20, 50));
	creatures.push_back(Creature("Pixarray", 19, 6, 25, 5.1, 100, 20, 50));
	creatures.push_back(Creature("Encryptix", 18, 7, 27, 6.0, 100, 20, 50));
	creatures.push_back(Creature("Recursior", 15, 10, 30, 5.9, 100, 20, 50));
	creatures.push_back(Creature("Boolbasaur", 21, 4, 30, 5.5, 100, 20, 50));
	creatures.push_back(Creature("Scriptor", 22, 3, 31, 5.8, 100, 20, 50));
	creatures.push_back(Creature("Codeeon", 19, 6, 28, 5.1, 100, 20, 50));
	creatures.push_back(Creature("Syntrax", 16, 9, 26, 4.9, 100, 20, 50));
	creatures.push_back(Creature("Phorlupe", 20, 5, 28, 6.1, 100, 20, 50));
	creatures.push_back(Creature("Seaplus", 17, 8, 25, 6.1, 100, 20, 50));
	creatures.push_back(Creature("Duewhyle", 17, 8, 25, 6.1, 100, 20, 50));
	

}

const vector<Creature>& CreatureList::getCreatures() const
{
	return creatures;
}

Creature CreatureList::getRandomCreature() const
{
	int randomIndex = rand() % creatures.size();
	return creatures[randomIndex];
}

void CreatureList::addCreature(const Creature& newCreature)
{
	creatures.push_back(newCreature);
}

