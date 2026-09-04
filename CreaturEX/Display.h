#ifndef DISPLAY_H
#define DISPLAY_H

#include "Creature.h"
#include "CreatureList.h"
#include "Player.h"

class Display
{
public:
	void showMenu(Player& player, CreatureList& creatureList);
	void displayBestiary(Player& player);
	void explore(Player& player, CreatureList& creatureList);
	void displayPlayer(Player& player);
	void displayPlayerStats(const Player& player);
	void displayCreatureStats(const Creature& creature);
	void clearScreen();
	void pauseForInput();
};

#endif
