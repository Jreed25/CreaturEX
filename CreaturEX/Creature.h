#ifndef CREATURE_H
#define CREATURE_H

#include <string>

using namespace std;

class Creature
{
private:
	string name;
	int level;
	int health;
	int totalHealth;
	int attack;
	int defense;
	double criticalHitChance;
	int expDrop;
	int goldDrop;
	int catchRate;

public:
	Creature();
	Creature(string name, int attack, int defense, int totalHealth, double criticalHitChance, int expDrop, int goldDrop, int catchRate);	// Creature Creation
	// Actions
	int takeDamage(int);
	int doDamage() const;
	int giveRandExp();
	int giveRandGold();
	void resetHealth();
	void setLevel(int);

	// Display
	string getName() const;
	int attackValue() const;
	int defenseValue() const;
	double getCriticalHC() const;
	int getHealth() const;
	int getTotalHealth() const;
	int getCatchRate() const;
	int getExpDrop() const;
	int getGoldDrop() const;

};

#endif
