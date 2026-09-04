#include "Creature.h"

#include <cstdlib>
#include <cmath>
#include <iostream>

Creature::Creature()
{
	name = "Unknown Creature";
	level = 1;
	attack = 10;
	defense = 5;
	totalHealth = 100;
	criticalHitChance = 7.7;
	expDrop = 100;
	goldDrop = 20;
	catchRate = 20;
	health = totalHealth;
}


Creature::Creature(std::string name, int attack, int defense, int totalHealth, 
	double criticalHitChance, int expDrop, int goldDrop, int catchRate)

	: name(name), level(1), attack(attack), defense(defense), totalHealth(totalHealth), 
	health(totalHealth), criticalHitChance(criticalHitChance), expDrop(expDrop), goldDrop(goldDrop), catchRate(catchRate) 
{
}


int Creature::takeDamage(int damage)
{
	// Defense reduces incoming damage by 25% of the creature's defense value.
	int netDamage = static_cast<int>(damage - (.25 * defense)); 
	if (netDamage < 0) 
	{
		netDamage = 0;	
	}

	health -= netDamage;

	if (health < 0) 
	{
		health = 0;
	}

	return netDamage;
}


int Creature::doDamage() const
{
	// Generate random damage from 1 to the creature's attack value.
	int damage = std::rand() % attack + 1; 

	if ((std::rand() % 100) < criticalHitChance) {
		damage = static_cast<int>(damage * 1.5);
		std::cout << "Critical Hit!\n";
	}

	return damage;
}


int Creature::giveRandExp()
{
    return (expDrop / 2) + (std::rand() % (expDrop - expDrop / 2 + 1));
}

int Creature::giveRandGold()
{
    return (goldDrop / 2) + (std::rand() % (goldDrop - goldDrop / 2 + 1));
}


void Creature::resetHealth()
{
	health = totalHealth;
}


void Creature::setLevel(int playerLevel)
{
    while (level < playerLevel)
    {
        ++level;

        attack += static_cast<int>(std::ceil(attack * 0.1));
        defense += static_cast<int>(std::ceil(defense * 0.1));
        totalHealth += static_cast<int>(std::ceil(totalHealth * 0.2));
        criticalHitChance += criticalHitChance * 0.1;
        expDrop += static_cast<int>(std::ceil(expDrop * 0.1));
        goldDrop += static_cast<int>(std::ceil(goldDrop * 0.1));
    }

    health = totalHealth;
}


std::string Creature::getName() const
{
	return name;
}

int Creature::getAttack() const
{
	return attack;
}

int Creature::getDefense() const
{
	return defense;
}

double Creature::getCriticalHitChance() const
{
	return criticalHitChance;
}

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