#ifndef PLAYER_H
#define PLAYER_H

#include "CreatureList.h"
#include "Creature.h"
#include "Shop.h"
#include "Item.h"
#include <vector>
#include <string>

// Class declaration for the user

class Player
{
private:
	vector<Creature> caughtCreatures;
	vector<Creature> encounteredCreatures;
	vector<Item> inventory;
	string name;
	int attack;
	int defense;
	int health;
	int totalHealth;
	int exp;
	int gold;
	int level;
	double criticalHitChance;

	const int MAX_POINTS = 60;

	void updateStats();	// Update stats level up

public:
	Player(string name = "Player");	// Player creation constructor

	// Combat
	int takeDamage(int);
	int takeReducedDamage(int);
	void heal();
	int doDamage() const;

	// Gains for player
	void gainExp(int);
	void gainGold(int);
	void subtractGold(int);
	void levelUp();

	// Getters
	string getName() const;
	int attackValue() const;
	int defenseValue() const;
	int getTotalHealth() const;
	int getHealth() const;
	int getGold() const;
	int getExp() const;
	int getLevel() const;
	double getCriticalHC() const;

	// Setters
	void setName(const string& newName);
	void setHealth(int newHealth);
	void setAttack(int newAttack);
	void setDefense(int newDefense);
	void setCriticalHitChance(double newCriticalHC);
	void setGold(int newGold);
	void setExp(int newExp);
	void setLevel(int newLevel);

	// Allocate stat points
	void allocateStatPoints(Player& player, CreatureList& creatureList);
	int getValidInput(const string& statName, int pointsRemaining);

	// Catch creature
	bool catchCreature(const Creature& creature);
	const vector<Creature>& getCaughtCreatures() const;
	void addCaughtCreature(const Creature& creature);

	// Encountered creatures bestiary display
	void addEncounteredCreature(const Creature& creature);
	const vector<Creature>& getEncounteredCreatures() const;

	//Inventory Management
	void displayInventory() const;
	const vector<Item>& getInventory() const;
	void setInventory(const vector<Item>& newInventory);
	void addItem(const Item& item);
	void removeItem(const string& itemName);
	bool hasItem(const string& itemName) const;
	bool isInventoryEmpty() const;
};
#endif
