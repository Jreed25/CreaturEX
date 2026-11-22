#include "SaveManager.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void Save::saveGame(const Player& player)
{
    std::ofstream outFile("playerData1.txt", std::ios::binary);
    if (!outFile)
    {
        std::cout << "Error opening file for saving data.\n";
        return;
    }


    size_t playerNameSize = player.getName().size();
    outFile.write(reinterpret_cast<const char*>(&playerNameSize), sizeof(playerNameSize));
    outFile.write(player.getName().c_str(), playerNameSize);


    serializeStats(player, outFile);

    serializeCreature(player, outFile, true);

    serializeCreature(player, outFile, false);

    serializeInventory(player, outFile);

    outFile.close();
    std::cout << "Player data saved successfully.\n";
}

void Save::loadGame(Player& player)
{
    std::ifstream inFile("playerData1.txt", std::ios::binary);
    if (!inFile)
    {
        std::cout << "Error opening file for loading data.\n";
        return;
    }


    size_t playerNameSize;
    inFile.read(reinterpret_cast<char*>(&playerNameSize), sizeof(playerNameSize));
    std::string playerName(playerNameSize, '\0');
    inFile.read(&playerName[0], playerNameSize);
    player.setName(playerName);


    deserializeStats(player, inFile);

    deserializeCreatures(player, inFile, true);  

    deserializeCreatures(player, inFile, false);  

    deserializeInventory(player, inFile);


    inFile.close();
    std::cout << "Player data loaded successfully.\n";
}

void Save::serializeStats(const Player& player, std::ofstream& outFile)
{
    int level = player.getLevel();
    int attack = player.getAttack();
    int defense = player.getDefense();
    int health = player.getHealth();
    int totalHealth = player.getTotalHealth();
    double criticalHC = player.getCriticalHitChance();
    int gold = player.getGold();
    int exp = player.getExp();

    outFile.write(reinterpret_cast<const char*>(&level), sizeof(level));
    outFile.write(reinterpret_cast<const char*>(&attack), sizeof(attack));
    outFile.write(reinterpret_cast<const char*>(&defense), sizeof(defense));
    outFile.write(reinterpret_cast<const char*>(&health), sizeof(health));
    outFile.write(reinterpret_cast<const char*>(&totalHealth), sizeof(totalHealth));
    outFile.write(reinterpret_cast<const char*>(&criticalHC), sizeof(criticalHC));
    outFile.write(reinterpret_cast<const char*>(&gold), sizeof(gold));
    outFile.write(reinterpret_cast<const char*>(&exp), sizeof(exp));
}

void Save::serializeCreature(const Player& player, std::ofstream& outFile, bool isCaught)
{
    const std::vector<Creature>& creatures = isCaught ? player.getCaughtCreatures() : player.getEncounteredCreatures();
    size_t creatureCount = creatures.size();
    outFile.write(reinterpret_cast<const char*>(&creatureCount), sizeof(creatureCount)); 


    for (const Creature& creature : creatures)
    {
        size_t nameSize = creature.getName().size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(creature.getName().c_str(), nameSize);

        int attack = creature.getAttack();
        int defense = creature.getDefense();
        int health = creature.getHealth();
        double criticalHC = creature.getCriticalHitChance();
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

void Save::serializeInventory(const Player& player, std::ofstream& outFile)
{
    const auto& inventory = player.getInventory();
    std::map<std::string, int> itemCounts;


    for (const auto& item : inventory)
    {
        itemCounts[item.getName()]++;
    }

    size_t uniqueItemCount = itemCounts.size();
    outFile.write(reinterpret_cast<const char*>(&uniqueItemCount), sizeof(uniqueItemCount));


    for (const auto& pair : itemCounts)
    {
        size_t nameSize = pair.first.size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(pair.first.c_str(), nameSize);
        outFile.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }
}

void Save::deserializeStats(Player& player, std::ifstream& inFile)
{
    int level;
    int attack;
    int defense;
    int health;
    int totalHealth;
    double criticalHC;
    int gold;
    int exp;

    inFile.read(reinterpret_cast<char*>(&level), sizeof(level));
    inFile.read(reinterpret_cast<char*>(&attack), sizeof(attack));
    inFile.read(reinterpret_cast<char*>(&defense), sizeof(defense));
    inFile.read(reinterpret_cast<char*>(&health), sizeof(health));
    inFile.read(reinterpret_cast<char*>(&totalHealth), sizeof(totalHealth));
    inFile.read(reinterpret_cast<char*>(&criticalHC), sizeof(criticalHC));
    inFile.read(reinterpret_cast<char*>(&gold), sizeof(gold));
    inFile.read(reinterpret_cast<char*>(&exp), sizeof(exp));

    player.setLevel(level);
    player.setAttack(attack);
    player.setDefense(defense);
    player.setHealth(health);
    player.setTotalHealth(totalHealth);
    player.setCriticalHitChance(criticalHC);
    player.setGold(gold);
    player.setExp(exp);
}

void Save::deserializeCreatures(Player& player, std::ifstream& inFile, bool isCaught)
{
    size_t creatureCount;
    inFile.read(reinterpret_cast<char*>(&creatureCount), sizeof(creatureCount));

    for (size_t i = 0; i < creatureCount; i++)
    {
        size_t nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        std::string name(nameSize, '\0');
        inFile.read(&name[0], nameSize);

        int attack, defense, health, expDrop, goldDrop, catchRate;
        double criticalHC;

        inFile.read(reinterpret_cast<char*>(&attack), sizeof(attack));
        inFile.read(reinterpret_cast<char*>(&defense), sizeof(defense));
        inFile.read(reinterpret_cast<char*>(&health), sizeof(health));
        inFile.read(reinterpret_cast<char*>(&criticalHC), sizeof(criticalHC));
        inFile.read(reinterpret_cast<char*>(&expDrop), sizeof(expDrop));
        inFile.read(reinterpret_cast<char*>(&goldDrop), sizeof(goldDrop));
        inFile.read(reinterpret_cast<char*>(&catchRate), sizeof(catchRate));

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

void Save::deserializeInventory(Player& player, std::ifstream& inFile)
{
    size_t inventorySize;
    inFile.read(reinterpret_cast<char*>(&inventorySize), sizeof(inventorySize));

    std::vector<Item> loadedInventory;

    for (size_t i = 0; i < inventorySize; i++)
    {
        size_t itemNameSize;
        inFile.read(reinterpret_cast<char*>(&itemNameSize), sizeof(itemNameSize));
        std::string itemName(itemNameSize, '\0');
        inFile.read(&itemName[0], itemNameSize);

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