#ifndef PLAYER_H
#define PLAYER_H

#include "CreatureList.h"
#include "Creature.h"
#include "Item.h"

#include <string>
#include <vector>

class Player
{
private:
	std::vector<Creature> caughtCreatures;
	std::vector<Creature> encounteredCreatures;
	std::vector<Item> inventory;
	std::string name;
	int attack;
	int defense;
	int health;
	int totalHealth;
	int exp;
	int gold;
	int level;
	double criticalHitChance;

	const int MAX_POINTS = 60;

	void updateStats();	

public:
	Player(std::string name = "Player");

	int takeDamage(int);
	int takeReducedDamage(int);
	void heal();
	int doDamage() const;

	void gainExp(int);
	void gainGold(int);
	void subtractGold(int);
	void levelUp();

	std::string getName() const;
	int getAttack() const;
	int getDefense() const;
	int getTotalHealth() const;
	int getHealth() const;
	int getGold() const;
	int getExp() const;
	int getLevel() const;
	double getCriticalHitChance() const;

	void setName(const std::string& newName);
	void setTotalHealth(int newTotalHealth);
	void setHealth(int newHealth);
	void setAttack(int newAttack);
	void setDefense(int newDefense);
	void setCriticalHitChance(double newCriticalHC);
	void setGold(int newGold);
	void setExp(int newExp);
	void setLevel(int newLevel);


	void allocateStatPoints(Player& player, CreatureList& creatureList);
	int getValidInput(const std::string& statName, int pointsRemaining);


	bool catchCreature(const Creature& creature);
	const std::vector<Creature>& getCaughtCreatures() const;
	void addCaughtCreature(const Creature& creature);


	void addEncounteredCreature(const Creature& creature);
	const std::vector<Creature>& getEncounteredCreatures() const;


	void displayInventory() const;
	const std::vector<Item>& getInventory() const;
	void setInventory(const std::vector<Item>& newInventory);
	void addItem(const Item& item);
	void removeItem(const std::string& itemName);
	bool hasItem(const std::string& itemName) const;
	bool isInventoryEmpty() const;
};

#endif