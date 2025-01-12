#include "Creature.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


// Function constructor for initialization

Creature::Creature()
{
	name = "Unknown Creature";
	attack = 10;
	defense = 5;
	totalHealth = 100;
	criticalHitChance = 7.7;
	expDrop = 100;
	goldDrop = 20;
	catchRate = 20;
	health = totalHealth;
}


// Function to create creatures

Creature::Creature(string name, int attack, int defense, int totalHealth, double criticalHitChance, int expDrop, int goldDrop, int catchRate)
	: name(name), attack(attack), defense(defense), totalHealth(totalHealth), health(totalHealth), criticalHitChance(criticalHitChance), expDrop(expDrop), goldDrop(goldDrop), catchRate(catchRate) {}


// Function for taking damage action

int Creature::takeDamage(int damage)
{
	int netDamage = static_cast<int>(damage - (.25 * defense)); // Defense scaling for damage
	if (netDamage < 0) netDamage = 0;		// Check for negative damage
	health -= netDamage;
	if (health < 0) health = 0;

	return netDamage;
}



// Function for doing damage action

int Creature::doDamage() const
{
	int damage = rand() % attack + 1; // Random amount of damage scaling with attack

	if ((rand() % 100) < (criticalHitChance)) {// Checking for critical hit
		damage = static_cast<int>(damage * 1.5);
		cout << "Critical Hit!\n";
	}

	return damage;
}


// Function to give a random amount of exp

int Creature::giveRandExp()
{
	// Ensure we are generating random exp between expDrop/2 and expDrop
	int exp = (expDrop / 2) + (rand() % (expDrop / 2));

	return exp;
}


// Function to give a random amount of gold

int Creature::giveRandGold()
{
	int gold = (goldDrop / 2) + (rand() % (goldDrop - (goldDrop / 2)));

	return gold;
}


// Reset creature health
void Creature::resetHealth()
{
	health = totalHealth;
}


// Function for setting creature level compared to player level

void Creature::setLevel(int playerLevel)
{
	level = playerLevel;

	// Update stats for each level
	for (int i = 1; i < level; i++)
	{
		attack += static_cast<int>(ceil(attack * .1));
		defense += static_cast<int>(ceil(defense * .1));
		totalHealth += static_cast<int>(ceil(totalHealth * .2));
		criticalHitChance += criticalHitChance * .1;
		expDrop += static_cast<int>(ceil(expDrop * .1));
		goldDrop += static_cast<int>(ceil(goldDrop * .1));

	}
}

// Function for returning creature name

string Creature::getName() const
{
	return name;
}

// Function for returning attack value 

int Creature::attackValue() const
{
	return attack;
}


// Function for returning defense value

int Creature::defenseValue() const
{
	return defense;
}


// Function for returning critical hit chance

double Creature::getCriticalHC() const
{
	return criticalHitChance;
}

// Function for returning health

int Creature::getHealth() const
{
	return health;
}

int Creature::getTotalHealth() const
{
	return totalHealth;
}

int Creature::getCatchRate() const
{
	return catchRate;
}

int Creature::getExpDrop() const
{
	return expDrop;
}
int Creature::getGoldDrop() const
{
	return goldDrop;
}

