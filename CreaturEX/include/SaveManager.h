#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "Creature.h"
#include "Player.h"

#include <iosfwd>

class Save
{
public:
	void saveGame(const Player& player);
	void loadGame(Player& player);

	void serializeInventory(const Player& player, std::ofstream& outFile);
	void serializeStats(const Player& player, std::ofstream& outFile);
	void serializeCreature(const Player& player, std::ofstream& outFile, bool isCaught);

	void deserializeInventory(Player& player, std::ifstream& inFile);
	void deserializeStats(Player& player, std::ifstream& inFile);
	void deserializeCreatures(Player& player, std::ifstream& inFile, bool isCaught);
};

#endif