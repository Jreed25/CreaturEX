#include "Display.h"
#include "Player.h"		
	
#include <cmath>
#include <cstdlib> 
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>

Player::Player(std::string name)
    : name(name), attack(0), defense(0), health(0), totalHealth(0),
      exp(0), gold(0), level(1), criticalHitChance(0)
{
}


int Player::takeDamage(int damage)
{
	// Defense reduces incoming damage by 25%.
	int netDamage = static_cast<int>(damage - (.25 * defense)); 
	if (netDamage < 0) netDamage = 0;		
	health -= netDamage;
	if (health < 0) health = 0;				

	return netDamage;
}

int Player::takeReducedDamage(int damage)
{
	// Defense reduces incoming damage by its full value while defending.
	int netReducedDamage = static_cast<int>(damage - defense); 
	if (netReducedDamage < 0) netReducedDamage = 0;		
	health -= netReducedDamage;
	if (health < 0) health = 0;		

	return netReducedDamage;
}

int Player::doDamage() const
{
	int damage = std::rand() % attack + 1;

	if ((std::rand() % 100) < (criticalHitChance)) 
	{
		damage = static_cast<int>(damage * 1.5);
		std::cout << "Critical Hit!\n";
	}

	return damage;
}

void Player::heal()
{
	health = totalHealth;
}


void Player::gainExp(int expAmount)
{
	exp += expAmount;
	if (exp >= level * 100) 
	{
		levelUp();
		std::cout << "You have leveled up. Good job!\n";
	}
}

void Player::gainGold(int goldAmount)
{
	gold += goldAmount;
}

void Player::subtractGold(int goldAmount)
{
	gold -= goldAmount;
}

void Player::levelUp()
{
	level++;
	exp = 0;
	updateStats(); 
}

void Player::updateStats()
{
	attack += static_cast<int>(std::ceil(attack * .1));
	defense += static_cast<int>(std::ceil(defense * .1));
	totalHealth += static_cast<int>(std::ceil(totalHealth * .2));
	criticalHitChance += criticalHitChance * .1;
}


std::string Player::getName() const
{
	return name;
}

int Player::getAttack() const
{
	return attack;
}

int Player::getDefense() const
{
	return defense;
}

int Player::getTotalHealth() const
{
	return totalHealth;
}

int Player::getHealth() const
{
	return health;
}

int Player::getGold() const
{
	return gold;
}

int Player::getExp() const
{
	return exp;
}

int Player::getLevel() const
{
	return level;
}

double Player::getCriticalHitChance() const
{
	return criticalHitChance;
}


void Player::setName(const std::string& newName)
{
	name = newName;
}

void Player::setTotalHealth(int newTotalHealth)
{
	totalHealth = newTotalHealth;
}

void Player::setHealth(int newHealth)
{
	health = newHealth;
}

void Player::setAttack(int newAttack)
{
	attack = newAttack;
}

void Player::setDefense(int newDefense)
{
	defense = newDefense;
}

void Player::setCriticalHitChance(double newCriticalHC)
{
	criticalHitChance = newCriticalHC;
}

void Player::setGold(int newGold)
{
	gold = newGold;
}

void Player::setExp(int newExp)
{
	exp = newExp;
}

void Player::setLevel(int newLevel)
{
	level = newLevel;
}


void Player::allocateStatPoints(Player& player, CreatureList& creatureList)
{
	int pointsRemaining = MAX_POINTS;


	Display display;
	display.clearScreen();

	std::cout << "Distribute " << MAX_POINTS << " points across the following stats:\n";
	std::cout << "----------------------------------------------------\n";
	std::cout << "| Stat                | Points Allocated |\n";
	std::cout << "----------------------------------------------------\n";
	std::cout << "| 1. Attack           | ?                |\n";
	std::cout << "| 2. Defense          | ?                |\n";
	std::cout << "| 3. Health           | ?                |\n";
	std::cout << "| 4. Critical Hit     | ?                |\n";
	std::cout << "----------------------------------------------------\n";
	std::cout << "Remaining points will be added to health.\n";


	std::cout << "Player Name: ";
	std::cin >> name;


	attack = getValidInput("Attack", pointsRemaining);
	pointsRemaining -= attack;

	defense = getValidInput("Defense", pointsRemaining);
	pointsRemaining -= defense;

	totalHealth = getValidInput("Health", pointsRemaining);
	pointsRemaining -= totalHealth;

	criticalHitChance = getValidInput("Critical Hit Chance", pointsRemaining);
	pointsRemaining -= static_cast<int>(criticalHitChance);	


	if (pointsRemaining > 0)
	{
		totalHealth += pointsRemaining;
	}


	gold = 0;
	exp = 0;
	level = 1;
	health = totalHealth;

	display.clearScreen();
	std::cout << "\n----------------------------------------------------\n";
	std::cout << "| Stat                | Points Allocated |\n";
	std::cout << "----------------------------------------------------\n";
	std::cout << "| 1. Attack           | " << std::setw(2) << attack << std::setw(17) << "             |\n";
	std::cout << "| 2. Defense          | " << std::setw(2) << defense << std::setw(17) << "             |\n";
	std::cout << "| 3. Health           | " << std::setw(2) << totalHealth << std::setw(17) << "            |\n";
	std::cout << "| 4. Critical Hit     | " << std::setw(2) << criticalHitChance << std::setw(17) << "  |\n";
	std::cout << "----------------------------------------------------\n";
	std::cout << "\nStat allocation complete!\n";

	display.pauseForInput();
	display.showMenu(player, creatureList);
}


int Player::getValidInput(const std::string& statName, int pointsRemaining)
{
	int input;


	while (true)
	{
		std::cout << statName << ": ";
		std::cin >> input;

		if (std::cin.fail()) 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid integer.\n";
		}
		else if (input >= 0 && input <= pointsRemaining)
		{
			return input;
		}
		else
		{
			std::cout << "Invalid input. Please enter a number between 0 and " << pointsRemaining << '\n';
		}
	}
}


bool Player::catchCreature(const Creature& creature)
{
	if (std::rand() % 100 < creature.getCatchRate())
	{
		std::cout << "You have caught " << creature.getName() << " good job!!\n";
		std::cout << creature.getName() << " added to your collection.\n";
		caughtCreatures.push_back(creature);
		return true;
	}
	else
	{
		std::cout << "You have failed to catch the " << creature.getName() << " good luck next time.\n";
		return false;
	}
}

void Player::addCaughtCreature(const Creature& creature)
{
	caughtCreatures.push_back(creature);
}

const std::vector<Creature>& Player::getCaughtCreatures() const
{
	return caughtCreatures;
}


void Player::addEncounteredCreature(const Creature& creature)
{
	encounteredCreatures.push_back(creature);
}

const std::vector<Creature>& Player::getEncounteredCreatures() const
{
	return encounteredCreatures;
}


void Player::displayInventory() const
{
	if (inventory.empty())
	{
		std::cout << "Your inventory is empty.\n";
		return;
	}

	std::map<std::string, int> itemCounts;

	for (const auto& item : inventory)
	{
		itemCounts[item.getName()]++;
	}

	std::cout << "\nYour Inventory:\n";
	for (const auto& pair : itemCounts)
	{
		std::cout << "- " << pair.first << ": " << pair.second << "\n";
	}
}

const std::vector<Item>& Player::getInventory() const
{
	return inventory;
}

void Player::setInventory(const std::vector<Item>& newInventory)
{
	inventory = newInventory;
}

void Player::addItem(const Item& item)
{
	inventory.push_back(item);
}

void Player::removeItem(const std::string& itemName)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		if (it->getName() == itemName)
		{
			inventory.erase(it);
			break;
		}
	}
}

bool Player::hasItem(const std::string& itemName) const 
{
	for (const auto& item : inventory) 
	{
		if (item.getName() == itemName) 
		{
			return true;
		}
	}
	return false;
}

bool Player::isInventoryEmpty() const 
{
	return inventory.empty();
}