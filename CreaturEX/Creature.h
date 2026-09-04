#ifndef CREATURE_H
#define CREATURE_H

#include <string>

class Creature
{
private:
	std::string name;
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
	Creature(std::string name, int attack, int defense, 
		int totalHealth, double criticalHitChance, int expDrop, 
		int goldDrop, int catchRate);

	int takeDamage(int);
	int doDamage() const;
	int giveRandExp();
	int giveRandGold();
	void resetHealth();
	void setLevel(int);


	std::string getName() const;
	int getAttack() const;
	int getDefense() const;
	double getCriticalHitChance() const;
	int getHealth() const;
	int getTotalHealth() const;
	int getCatchRate() const;
	int getExpDrop() const;
	int getGoldDrop() const;
};

#endif