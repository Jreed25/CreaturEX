// Implementation file for the Player class
#include "Player.h"		
#include "Display.h"	
#include "Creature.h"

#include <iostream>
#include <fstream> 
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <map>

using namespace std;


// Constructor for player (default values for stats)

Player::Player(string name)
	: name(name), totalHealth(0), attack(0), defense(0), gold(0), level(1), exp(0), criticalHitChance(0)
{
}


//Combat******************
//************************
int Player::takeDamage(int damage)
{
	int netDamage = static_cast<int>(damage - (.25 * defense)); // Defense scaling for damage
	if (netDamage < 0) netDamage = 0;		// Check for negative damage
	health -= netDamage;
	if (health < 0) health = 0;				//  Prevent health from going below 0

	return netDamage;
}


int Player::takeReducedDamage(int damage)
{
	int netReducedDamage = static_cast<int>(damage - (1 * defense)); // Defense scaling for damage
	if (netReducedDamage < 0) netReducedDamage = 0;		// Check for negative damage
	health -= netReducedDamage;
	if (health < 0) health = 0;		//  Prevent health from going below 0

	return netReducedDamage;
}


int Player::doDamage() const
{
	int damage = rand() % attack + 1; // Random amount of damage scaling with attack

	if ((rand() % 100) < (criticalHitChance)) {// Checking for critical hit
		damage = static_cast<int>(damage * 1.5);
		cout << "Critical Hit!\n";
	}

	return damage;
}


void Player::heal()
{

	health = totalHealth;

}


// Gains for player*************
//******************************
void Player::gainExp(int expAmount)
{

	exp += expAmount;
	if (exp >= level * 100) // Threshold for leveling
	{
		levelUp();
		cout << "You have leveled up. Good job!\n";
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
	updateStats(); // Call update stats for level up
}

void Player::updateStats()
{
	attack += static_cast<int>(ceil(attack * .1));
	defense += static_cast<int>(ceil(defense * .1));
	totalHealth += static_cast<int>(ceil(totalHealth * .2));
	criticalHitChance += criticalHitChance * .1;
}


// Getters ********************
//*****************************
string Player::getName() const
{
	return name;
}


int Player::attackValue() const
{
	return attack;
}


int Player::defenseValue() const
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


double Player::getCriticalHC() const
{
	return criticalHitChance;
}


// Setters *******************************
//****************************************
void Player::setName(const string& newName)
{
	name = newName;
}

void Player::setHealth(int newHealth)
{
	totalHealth = newHealth;
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


// Stat point allocation

void Player::allocateStatPoints(Player& player, CreatureList& creatureList)
{
	int pointsRemaining = MAX_POINTS;


	Display display;
	display.clearScreen();

	cout << "Distribute " << MAX_POINTS << " points across the following stats:\n";
	cout << "----------------------------------------------------\n";
	cout << "| Stat                | Points Allocated |\n";
	cout << "----------------------------------------------------\n";
	cout << "| 1. Attack           | ?                |\n";
	cout << "| 2. Defense          | ?                |\n";
	cout << "| 3. Health           | ?                |\n";
	cout << "| 4. Critical Hit     | ?                |\n";
	cout << "----------------------------------------------------\n";
	cout << "Remaining points will be added to health.\n";


	// Name 
	cout << "Player Name: ";
	cin >> name;


	// Attack
	attack = getValidInput("Attack", pointsRemaining);
	pointsRemaining -= attack;


	// Defense
	defense = getValidInput("Defense", pointsRemaining);
	pointsRemaining -= defense;


	// Health
	totalHealth = getValidInput("Health", pointsRemaining);
	pointsRemaining -= totalHealth;


	// Critical Hit Chance
	criticalHitChance = getValidInput("Critical Hit Chance", pointsRemaining);
	static_cast<int>(pointsRemaining -= criticalHitChance);


	// Allocate points left over
	if (pointsRemaining > 0)
	{
		totalHealth += pointsRemaining;
	}


	// Initialize these values
	gold = 0;
	exp = 0;
	level = 1;
	health = totalHealth;

	display.clearScreen();
	// Display their allocated stats
	cout << "\n----------------------------------------------------\n";
	cout << "| Stat                | Points Allocated |\n";
	cout << "----------------------------------------------------\n";
	cout << "| 1. Attack           | " << setw(2) << attack << setw(17) << "             |\n";
	cout << "| 2. Defense          | " << setw(2) << defense << setw(17) << "             |\n";
	cout << "| 3. Health           | " << setw(2) << totalHealth << setw(17) << "            |\n";
	cout << "| 4. Critical Hit     | " << setw(2) << criticalHitChance << setw(17) << "  |\n";
	cout << "----------------------------------------------------\n";
	cout << "\nStat allocation complete!\n";

	display.pauseforInput();
	display.showMenu(player, creatureList);

}


// Check for valid input

int Player::getValidInput(const string& statName, int pointsRemaining)
{
	int input;

	// Keep it looping 
	while (true)
	{
		cout << statName << ": ";
		cin >> input;

		if (cin.fail()) {
			// Clear the input stream and ignore invalid input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a valid integer.\n";
		}
		else if (input >= 0 && input <= pointsRemaining)
		{
			return input;
		}
		else
		{
			cout << "Invalid input. Please enter a number between 0 and " << pointsRemaining << endl;
		}
	}
}


// Caught creatures************
//*****************************
bool Player::catchCreature(const Creature& creature)
{
	if (rand() % 100 > creature.getCatchRate())
	{
		cout << "You have caught " << creature.getName() << " good job!!\n";
		cout << creature.getName() << " added to your collection.\n";
		caughtCreatures.push_back(creature);
		return true;
	}
	else
	{
		cout << "You have failed to catch the " << creature.getName() << " good luck next time.\n";
		return false;
	}
}

void Player::addCaughtCreature(const Creature& creature)
{
	caughtCreatures.push_back(creature);
}

const vector<Creature>& Player::getCaughtCreatures() const
{
	return caughtCreatures;
}


// Enctounters ********************
//*********************************
void Player::addEncounteredCreature(const Creature& creature)
{
	encounteredCreatures.push_back(creature);
}

const vector<Creature>& Player::getEncounteredCreatures() const
{
	return encounteredCreatures;
}


// Inventory Management***********
//********************************
void Player::displayInventory() const
{
	if (inventory.empty())
	{
		cout << "Your inventory is empty.\n";
		return;
	}

	map<string, int> itemCounts;

	for (const auto& item : inventory)
	{
		itemCounts[item.getName()]++;
	}

	std::cout << "\nYour Inventory:\n";
	for (const auto& pair : itemCounts)
	{
		cout << "- " << pair.first << ": " << pair.second << "\n";
	}

}

const vector<Item>& Player::getInventory() const
{
	return inventory;
}

void Player::setInventory(const vector<Item>& newInventory)
{
	inventory = newInventory;
}

void Player::addItem(const Item& item)
{
	inventory.push_back(item);
}

void Player::removeItem(const string& itemName)
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

bool Player::hasItem(const std::string& itemName) const {
	for (const auto& item : inventory) {
		if (item.getName() == itemName) {
			return true;
		}
	}
	return false;
}

bool Player::isInventoryEmpty() const {
	return inventory.empty();
}