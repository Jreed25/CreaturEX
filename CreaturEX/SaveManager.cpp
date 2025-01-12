#include "Player.h"
#include "Creature.h"
#include "SaveManager.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Save/load player values*******
//*******************************
void Save::saveGame(const Player& player)
{
    ofstream outFile("playerData1.txt", ios::binary);
    // Check for error opening file
    if (!outFile)
    {
        cout << "Error opening file for saving data.\n";
    }

    // Save the players name
    size_t playerNameSize = player.getName().size();
    outFile.write(reinterpret_cast<const char*>(&playerNameSize), sizeof(playerNameSize));
    outFile.write(player.getName().c_str(), playerNameSize);


    // Save player stats
    serializeStats(player, outFile);

    // Save caught creatures
    serializeCreature(player, outFile, true);

    // Save encountered creatures
    serializeCreature(player, outFile, false);

    // Save items and item counts
    serializeInventory(player, outFile);

    outFile.close();
    cout << "Player data save successfully.\n";
}

void Save::loadGame(Player& player)
{
    // Open the input file stream to load data
    ifstream inFile("playerData1.txt", ios::binary);
    // Check for error opening file
    if (!inFile)
    {
        cout << "Error opening file for loading data.\n";
        return;
    }

    // Set the players name
    size_t playerNameSize;
    inFile.read(reinterpret_cast<char*>(&playerNameSize), sizeof(playerNameSize));
    string playerName(playerNameSize, '\0');
    inFile.read(&playerName[0], playerNameSize);
    player.setName(playerName);

    // Load player stats
    deserializeStats(player, inFile);

    // Load caught creatures
    deserializeCreatures(player, inFile, true);  // Pass true for caught creatures

    // Load encountered creatures
    deserializeCreatures(player, inFile, false);  // Pass false for encountered creatures

    // Load items and item counts
    deserializeInventory(player, inFile);

    inFile.close();
    cout << "Player data loaded successfully.\n";
}


// Serialization for players*******
//*********************************
void Save::serializeStats(const Player& player, ofstream& outFile)
{
    // Players stats
    int level = player.getLevel();
    int attack = player.attackValue();
    int defense = player.defenseValue();
    int health = player.getHealth();
    double criticalHC = player.getCriticalHC();
    int gold = player.getGold();
    int exp = player.getExp();

    // Save the players stats
    outFile.write(reinterpret_cast<const char*>(&level), sizeof(level));
    outFile.write(reinterpret_cast<const char*>(&attack), sizeof(attack));
    outFile.write(reinterpret_cast<const char*>(&defense), sizeof(defense));
    outFile.write(reinterpret_cast<const char*>(&health), sizeof(health));
    outFile.write(reinterpret_cast<const char*>(&criticalHC), sizeof(criticalHC));
    outFile.write(reinterpret_cast<const char*>(&gold), sizeof(gold));
    outFile.write(reinterpret_cast<const char*>(&exp), sizeof(exp));


}

void Save::serializeCreature(const Player& player, ofstream& outFile, bool isCaught)
{
    const vector<Creature>& creatures = isCaught ? player.getCaughtCreatures() : player.getEncounteredCreatures();
    size_t creatureCount = creatures.size();
    outFile.write(reinterpret_cast<const char*>(&creatureCount), sizeof(creatureCount)); // Write the number of caught creatures

    // Loop through each creature
    for (const Creature& creature : creatures)
    {
        // Save each creatures name
        size_t nameSize = creature.getName().size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));  // Write name size
        outFile.write(creature.getName().c_str(), nameSize);

        // Save each creatures stats
        int attack = creature.attackValue();
        int defense = creature.defenseValue();
        int health = creature.getHealth();
        double criticalHC = creature.getCriticalHC();
        int expDrop = creature.getExpDrop();
        int goldDrop = creature.getGoldDrop();
        int catchRate = creature.getCatchRate();

        outFile.write(reinterpret_cast<const char*>(&attack), sizeof(attack));
        outFile.write(reinterpret_cast<const char*>(&defense), sizeof(defense));
        outFile.write(reinterpret_cast<const char*>(&health), sizeof(health));
        outFile.write(reinterpret_cast<const char*>(&criticalHC), sizeof(criticalHC));
        outFile.write(reinterpret_cast<const char*>(&expDrop), sizeof(expDrop));
        outFile.write(reinterpret_cast<const char*>(&goldDrop), sizeof(goldDrop));
        outFile.write(reinterpret_cast<const char*>(&catchRate), sizeof(catchRate));
    }

}

void Save::serializeInventory(const Player& player, ofstream& outFile)
{
    const auto& inventory = player.getInventory();
    map<string, int> itemCounts;

    // Count items by name
    for (const auto& item : inventory)
    {
        itemCounts[item.getName()]++;
    }

    // Save unique items
    size_t uniqueItemCount = itemCounts.size();
    outFile.write(reinterpret_cast<const char*>(&uniqueItemCount), sizeof(uniqueItemCount));


    // Save each item name and count
    for (const auto& pair : itemCounts)
    {
        size_t nameSize = pair.first.size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(pair.first.c_str(), nameSize);
        outFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }
}


// Deserialization for player*******
//**********************************
void Save::deserializeStats(Player& player, ifstream& inFile)
{

    int level;
    int attack;
    int defense;
    int health;
    double criticalHC;
    int gold;
    int exp;

    // Read saved stats
    inFile.read(reinterpret_cast<char*>(&level), sizeof(level));
    inFile.read(reinterpret_cast<char*>(&attack), sizeof(attack));
    inFile.read(reinterpret_cast<char*>(&defense), sizeof(defense));
    inFile.read(reinterpret_cast<char*>(&health), sizeof(health));
    inFile.read(reinterpret_cast<char*>(&criticalHC), sizeof(criticalHC));
    inFile.read(reinterpret_cast<char*>(&gold), sizeof(gold));
    inFile.read(reinterpret_cast<char*>(&exp), sizeof(exp));

    // Set the read stats
    player.setLevel(level);
    player.setAttack(attack);
    player.setDefense(defense);
    player.setHealth(health);
    player.setCriticalHitChance(criticalHC);
    player.setGold(gold);
    player.setExp(exp);
}

void Save::deserializeCreatures(Player& player, ifstream& inFile, bool isCaught)
{
    // Find the size of the creatures that needs to read
    size_t creatureCount;
    inFile.read(reinterpret_cast<char*>(&creatureCount), sizeof(creatureCount));

    for (size_t i = 0; i < creatureCount; i++)
    {
        // Read creature name
        size_t nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        string name(nameSize, '\0');
        inFile.read(&name[0], nameSize);

        // Read creature stats
        int attack, defense, health, expDrop, goldDrop, catchRate;
        double criticalHC;

        inFile.read(reinterpret_cast<char*>(&attack), sizeof(attack));
        inFile.read(reinterpret_cast<char*>(&defense), sizeof(defense));
        inFile.read(reinterpret_cast<char*>(&health), sizeof(health));
        inFile.read(reinterpret_cast<char*>(&criticalHC), sizeof(criticalHC));
        inFile.read(reinterpret_cast<char*>(&expDrop), sizeof(expDrop));
        inFile.read(reinterpret_cast<char*>(&goldDrop), sizeof(goldDrop));
        inFile.read(reinterpret_cast<char*>(&catchRate), sizeof(catchRate));


        // Set the creature to the right vector
        Creature creature(name, attack, defense, health, criticalHC, expDrop, goldDrop, catchRate);

        if (isCaught)
        {
            player.addCaughtCreature(creature);
        }
        else
        {
            player.addEncounteredCreature(creature);
        }
    }
}

void Save::deserializeInventory(Player& player, ifstream& inFile)
{
    // Find the size of the inventory that needs to read
    size_t inventorySize;
    inFile.read(reinterpret_cast<char*>(&inventorySize), sizeof(inventorySize));

    vector<Item> loadedInventory;

    // Read/load all the different types of items written into the file
    for (size_t i = 0; i < inventorySize; i++)
    {
        // Read item name
        size_t itemNameSize;
        inFile.read(reinterpret_cast<char*>(&itemNameSize), sizeof(itemNameSize));
        string itemName(itemNameSize, '\0');
        inFile.read(&itemName[0], itemNameSize);

        // Read the amount of each item
        int itemValue;
        inFile.read(reinterpret_cast<char*>(&itemValue), sizeof(itemValue));

        for (int i = 0; i < itemValue; ++i)
        {
            Item item(itemName, 0);
            loadedInventory.push_back(item);
        }

    }

    player.setInventory(loadedInventory);
}

