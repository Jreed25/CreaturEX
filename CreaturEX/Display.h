
#ifndef DISPLAY_H
#define DISPLAY_H


#include "Player.h"
#include "Creature.h"
#include "CreatureList.h"


class Display
{
public:
	void showMenu(Player& player, CreatureList& creatureList);
	void displayBestiary(Player& player, CreatureList& creatureList);
	void explore(Player& player, CreatureList& creatureList);
	void displayPlayerStats(const Player& player);
	void displayCreatureStats(const Creature& creature);
	void clearScreen();
	void pauseforInput();
};

#endif
