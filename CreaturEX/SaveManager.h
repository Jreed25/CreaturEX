#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "Player.h"
#include "Creature.h"


class Save
{
public:
	void saveGame(const Player& player);
	void loadGame(Player& player);

	// Serialization
	void serializeInventory(const Player& player, ofstream& outFile);
	void serializeStats(const Player& player, ofstream& outFile);
	void serializeCreature(const Player& player, ofstream& outFile, bool isCaught);

	// Deserialization
	void deserializeInventory(Player& player, ifstream& inFile);
	void deserializeStats(Player& player, ifstream& inFile);
	void deserializeCreatures(Player& player, ifstream& inFile, bool isCaught);
};

#endif
