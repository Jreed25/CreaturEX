// Implementation file for all display functions

// Headers
#include "Display.h"
#include "Player.h"
#include "Creature.h"
#include "CreatureList.h"
#include "Encounter.h"
#include "SaveManager.h"
#include "Shop.h"

#include <iostream>
#include<iomanip>
#include <cstdlib>
#include <vector>

using namespace std;


// Function for showing Creatara menu

void Display::showMenu(Player& player, CreatureList& creatureList)
{
    Save save;
    Shop shop;
    bool inShop = true;

    int choice = 0;

    // Display menu
    while (choice != 5) {
        clearScreen();
        player.heal();  // Heal player

        cout << "--- Welcome back to Creatara! ---\n";
        cout << "1. Explore\n";
        cout << "2. Shop\n";
        cout << "3. Bestiary\n";
        cout << "4. Character\n";
        cout << "5. Save Game\n";
        cout << "6. Quit Game\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Case for menu choice
        switch (choice) {
        case 1:

            explore(player, creatureList);
            break;
        case 2:

            shop.displayShopInventory(player);
            break;
        case 3:

            displayBestiary(player, creatureList);
            break;
        case 4:

            displayPlayer(player, creatureList);
            break;
        case 5:

            save.saveGame(player);
            break;
        case 6:

            exit(EXIT_FAILURE);
            break;
        default:

            cout << "Invalid input. Try again.\n\n";
            break;
        }

    }
}


// Function for displaying bestiary

void Display::displayBestiary(Player& player, CreatureList& creatureList)
{
    int i = 0;
    int choice = 0;
    const vector<Creature>& allEncounteredCreatures = player.getEncounteredCreatures();
    const vector<Creature>& allCaughtCreatures = player.getCaughtCreatures();

    clearScreen();
    cout << "--- Bestiary ---\n";
    cout << "1. Encountered Creatures\n";
    cout << "2. Caught Creatures\n";
    cout << "3. Back to town square \n";
    cout << "Which would you like to view? \n";
    cin >> choice;


    switch (choice)
    {
    case 1:
        clearScreen();
        if (allEncounteredCreatures.empty())
        {
            // Checking if bestiary is empty
            cout << "You haven't encountered any creatures yet. \n";
        }
        else
        {
            for (const Creature& creature : allEncounteredCreatures)
            {

                i++;
                cout << i << ". " << creature.getName() << endl;

            }
        }
        pauseforInput();
        break;
    case 2:
        clearScreen();
        if (allCaughtCreatures.empty())
        {
            // Checking if bestiary is empty
            cout << "You haven't caught any creatures yet. \n";
        }
        else
        {
            for (const Creature& creature : allCaughtCreatures)
            {

                i++;
                cout << i << ". " << creature.getName() << endl;

            }
        }
        pauseforInput();
        break;

    case 3:

        showMenu(player, creatureList);
        break;
    default:

        cout << "Invalid input. Try again.\n";
        break;
    }


}


// Function for displaying stats

void Display::displayPlayerStats(const Player& player)
{
    clearScreen();
    cout << "--- Stats ---\n";
    cout << "Attack: " << player.attackValue() << endl;
    cout << "Defense: " << player.defenseValue() << endl;
    cout << "Health: " << player.getTotalHealth() << endl;
    cout << "Critical Hit Chance: " << player.getCriticalHC() << endl;
    cout << "Level: " << player.getLevel() << endl;
    cout << "Exp: " << player.getExp() << " (Next Level: " << (player.getLevel() * 100) - player.getExp() << " exp)" << endl;
    cout << "Gold: " << player.getGold() << endl << endl;


    // Pause to allow the player to review stats
    pauseforInput();
}


// Function for displaying Creature stats

void Display::displayCreatureStats(const Creature& creature)
{
    clearScreen();
    cout << "---- Stats ----\n";
    cout << "Name: " << creature.getName() << endl;
    cout << "Attack: " << creature.attackValue() << endl;
    cout << "Defense: " << creature.defenseValue() << endl;
    cout << "Health: " << creature.getHealth() << endl;


    // Pause to allow the player to review stats
    pauseforInput();

}


// Function for choosing to explore

void Display::explore(Player& player, CreatureList& creatureList)
{
    int choice = 0;
    Encounter encounter;

    // Menu for direction
    while (choice != 4)
    {
        clearScreen();
        cout << "You chose to explore. Good luck!\n";
        cout << "Choose your direction\n";
        cout << "1. Left\n";
        cout << "2. Straight\n";
        cout << "3. Right\n";
        cout << "4. Go back home\n";
        cout << "Enter your choice: \n";
        cin >> choice;


        // Switch case for choices
        switch (choice)
        {
        case 1:

            cout << "You chose to go left.\n";
            cout << "Now heading left.\n";
            encounter.handleEncounter(player, creatureList);    // Creature encounter
            break;
        case 2:

            cout << "You chose to go straight.\n";
            cout << "Now heading straight.\n";
            encounter.handleEncounter(player, creatureList);
            break;
        case 3:

            cout << "You chose to go right.\n";
            cout << "Now heading right.\n";
            encounter.handleEncounter(player, creatureList);
            break;
        case 4:

            return;
        default:


            cout << "Invalid input. Try again. \n\n";
            break;
        }
    }
}


// Clear screen

void Display::clearScreen()
{
    system("CLS");  // Clears the screen on Windows
}


// Function for pausing for input

void Display::pauseforInput()
{
    cout << "Press Enter to return...";
    cin.ignore();  // Clears the newline character left in the buffer
    cin.get();     // Waits for Enter key press
}

void Display::displayPlayer(Player& player, CreatureList& creatureList)
{
    clearScreen();
    // Variables
    int choice = 0;
    
    // Display choice menu
    cout << "--- Character Details ---\n";
    cout << "1. View Stats\n";
    cout << "2. View Inventory\n";
    cout << "3. Back to town square \n";
    cout << "Enter your choice: \n";
    cin >> choice;

    switch (choice) {
        case 1:

            displayPlayerStats(player);
            break;
        case 2:

            player.displayInventory();

            cout << "Press Enter to return...";
            cin.ignore();  // Clears the newline character left in the buffer
            cin.get();     // Waits for Enter key press
            break;
        case 3:

            return;
         
    }
}