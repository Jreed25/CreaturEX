#include "Creature.h"
#include "CreatureList.h"
#include "Display.h"
#include "Encounter.h"
#include "Player.h"
#include "SaveManager.h"
#include "Shop.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

void Display::showMenu(Player& player, CreatureList& creatureList)
{
    Save save;
    Shop shop;

    int choice = 0;

    while (choice != 6) 
    {
        clearScreen();
        player.heal();  

        std::cout << "--- Welcome back to Creatara! ---\n";
        std::cout << "1. Explore\n";
        std::cout << "2. Shop\n";
        std::cout << "3. Bestiary\n";
        std::cout << "4. Character\n";
        std::cout << "5. Save Game\n";
        std::cout << "6. Quit Game\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) 
        {
        case 1:
            explore(player, creatureList);
            break;
        case 2:
            shop.displayShopInventory(player);
            break;
        case 3:
            displayBestiary(player);
            break;
        case 4:
            displayPlayer(player);
            break;
        case 5:
            save.saveGame(player);
            break;
        case 6:
            return;
        default:
            std::cout << "Invalid input. Try again.\n\n";
            break;
        }
    }
}

void Display::displayBestiary(Player& player)
{
    int choice = 0;
    const std::vector<Creature>& allEncounteredCreatures = player.getEncounteredCreatures();
    const std::vector<Creature>& allCaughtCreatures = player.getCaughtCreatures();

    clearScreen();
    std::cout << "--- Bestiary ---\n";
    std::cout << "1. Encountered Creatures\n";
    std::cout << "2. Caught Creatures\n";
    std::cout << "3. Back to town square\n";
    std::cout << "Which would you like to view?\n";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        clearScreen();
        if (allEncounteredCreatures.empty())
        {
            std::cout << "You haven't encountered any creatures yet.\n";
        }
        else
        {
            int i = 1;
            
            for (const Creature& creature : allEncounteredCreatures)
            {
                std::cout << i++ << ". " << creature.getName() << '\n';
            }
        }

        pauseForInput();
        break;
    case 2:
        clearScreen();
        if (allCaughtCreatures.empty())
        {   
            std::cout << "You haven't caught any creatures yet.\n";
        }
        else
        {
            int i = 1;
            
            for (const Creature& creature : allCaughtCreatures)
            {
                std::cout << i++ << ". " << creature.getName() << '\n';
            }
        }

        pauseForInput();
        break;
    case 3:
        return;
    default:
        std::cout << "Invalid input. Try again.\n";
        break;
    }
}

void Display::displayPlayerStats(const Player& player)
{
    clearScreen();
    std::cout << "--- Stats ---\n";
    std::cout << "Attack: " << player.getAttack() << '\n';
    std::cout << "Defense: " << player.getDefense() << '\n';
    std::cout << "Health: " << player.getTotalHealth() << '\n';
    std::cout << "Critical Hit Chance: " << player.getCriticalHitChance() << '\n';
    std::cout << "Level: " << player.getLevel() << '\n';
    std::cout << "Exp: " << player.getExp() << " (Next Level: " << (player.getLevel() * 100) - player.getExp() << " exp)" << '\n';
    std::cout << "Gold: " << player.getGold() << "\n\n";

    pauseForInput();
}

void Display::displayCreatureStats(const Creature& creature)
{
    clearScreen();
    std::cout << "---- Stats ----\n";
    std::cout << "Name: " << creature.getName() << '\n';
    std::cout << "Attack: " << creature.getAttack() << '\n';
    std::cout << "Defense: " << creature.getDefense() << '\n';
    std::cout << "Health: " << creature.getHealth() << '\n';

    pauseForInput();
}

void Display::displayPlayer(Player& player)
{
    clearScreen();
    int choice = 0;
    
    std::cout << "--- Character Details ---\n";
    std::cout << "1. View Stats\n";
    std::cout << "2. View Inventory\n";
    std::cout << "3. Back to town square\n";
    std::cout << "Enter your choice: \n";
    std::cin >> choice;

    switch (choice) 
    {
    case 1:
        displayPlayerStats(player);
        break;
    case 2:
        player.displayInventory();

        pauseForInput();   
        break;
    case 3:
        return;
    default:
        std::cout << "Invalid input. Try again.\n";
        pauseForInput();
        break;     
    }
}

void Display::explore(Player& player, CreatureList& creatureList)
{
    int choice = 0;
    Encounter encounter;

    while (choice != 4)
    {
        clearScreen();
        std::cout << "You chose to explore. Good luck!\n";
        std::cout << "Choose your direction\n";
        std::cout << "1. Left\n";
        std::cout << "2. Straight\n";
        std::cout << "3. Right\n";
        std::cout << "4. Go back home\n";
        std::cout << "Enter your choice: \n";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "You chose to go left.\n";
            std::cout << "Now heading left.\n";
            encounter.handleEncounter(player, creatureList); 
            break;
        case 2:
            std::cout << "You chose to go straight.\n";
            std::cout << "Now heading straight.\n";
            encounter.handleEncounter(player, creatureList);
            break;
        case 3:
            std::cout << "You chose to go right.\n";
            std::cout << "Now heading right.\n";
            encounter.handleEncounter(player, creatureList);
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid input. Try again.\n\n";
            break;
        }
    }
}


void Display::clearScreen()
{
    system("clear"); 
}

void Display::pauseForInput()
{
    std::cout << "Press Enter to return...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();  
}