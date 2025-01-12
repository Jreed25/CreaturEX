// Implementation file for handling the encounter with the player and creature

#include "Encounter.h"
#include "Creature.h"
#include "Player.h"
#include "Display.h"
#include "CreatureList.h"


#include <iostream>
#include <cstdlib>


using namespace std;
void Encounter::handleEncounter(Player& player, CreatureList& creatureList)
{

    do {
        Creature randomCreature = creatureList.getRandomCreature();

        randomCreature.setLevel(player.getLevel());

        randomCreature.resetHealth();
        Display display;

        // Switch case choices/counters
        int choice = 0;
        int turnCounter = 1;
        char healChoice = ' ';
        bool isCaught = false;

        // Damage variables
        int damage = 0;
        int scaledPlayerDamage = 0;
        int scaledCreatureDamage = 0;
        int health = randomCreature.getHealth();

        // Gain variables
        int exp;
        int gold;


        // Display choices/menu 
        display.clearScreen();
        cout << "You have encountered a " << randomCreature.getName() << "!\n";
        player.addEncounteredCreature(randomCreature);

        while (randomCreature.getHealth() > 0 && player.getHealth() > 0 && !isCaught)
        {
            // Check if it is first turn or not so player can defend mid battle
            if (turnCounter <= 1)
            {
                cout << "1. Attack \n";
                cout << "2. Check Stats \n";
                cout << "3. Catch Creature \n";
                cout << "4. Run \n";

            }
            else
            {
                cout << "1. Attack \n";
                cout << "2. Defend \n";
                cout << "3. Catch Creature \n";
                cout << "4. Run \n";

            }

            cout << "What do you do?\n";
            cin >> choice;

            switch (choice)
            {
            case 1:


                damage = player.doDamage();
                scaledPlayerDamage = randomCreature.takeDamage(damage);

                cout << "You did " << scaledPlayerDamage << " damage to " << randomCreature.getName() << ". "
                    << randomCreature.getHealth() << "/" << randomCreature.getTotalHealth() << " left.\n";

                // Check if creature is dead
                if (randomCreature.getHealth() <= 0) {
                    cout << randomCreature.getName() << " has been defeated!\n";
                    exp = randomCreature.giveRandExp();
                    gold = randomCreature.giveRandGold();
                    cout << "Congratulations you have been given " << exp << " exp and " << gold << " gold!!!\n";
                    player.gainExp(exp);
                    player.gainGold(gold);
                    break;
                }



                // Creature attacks back
                damage = randomCreature.doDamage();
                scaledCreatureDamage = player.takeDamage(damage);
                cout << randomCreature.getName() << " did " << scaledCreatureDamage << " damage to you. "
                    << player.getHealth() << "/" << player.getTotalHealth() << " left.\n";



                // Check if player is dead
                if (player.getHealth() <= 0) {
                    cout << "You have been defeated by " << randomCreature.getName() << "!\n";

                    display.pauseforInput();


                    display.showMenu(player, creatureList);
                    return;
                }


                // Pause to allow the player to review 
                cout << "Press Enter for next turn...";
                cin.ignore();  // Clears the newline character left in the buffer
                cin.get();     // Waits for Enter key press
                break;
            case 2:
                if (turnCounter <= 1)
                {
                    display.displayCreatureStats(randomCreature);
                }
                else
                {
                    cout << "You brace for the enemy's attack, reducing incoming damage!\n";
                    // Creature attacks 
                    damage = randomCreature.doDamage();
                    scaledCreatureDamage = player.takeReducedDamage(damage);  // Defense (reduced damage)
                    cout << randomCreature.getName() << " did " << scaledCreatureDamage << " damage to you. "
                        << player.getHealth() << "/" << player.getTotalHealth() << " left.\n";
                }


                break;
            case 3:

                isCaught = player.catchCreature(randomCreature);
                break;
            case 4:


                return;
            default:


                cout << "Invalid input. Please try again\n";
                continue;
            }
            // Inc turn counter
            turnCounter++;
        }

        if (player.getHealth() > 0)
        {
            cout << "Would you like to fight another creature or return to base to heal?\n";
            cout << "1. Fight another \n";
            cout << "2. Go to base and heal \n";
            cin >> choice;

            switch (choice)
            {
            case 1:

                continue;
            case 2:

                player.heal();
                display.showMenu(player, creatureList);
                return;
            default:

                cout << "Invalid input. Returning to the menu.\n";
                display.showMenu(player, creatureList);
                return;
            }
        }

    } while (player.getHealth() > 0);
}