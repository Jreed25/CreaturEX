#include "Creature.h"
#include "CreatureList.h"
#include "Display.h"
#include "Encounter.h"
#include "Player.h"

#include <iostream>

void Encounter::handleEncounter(Player& player, CreatureList& creatureList)
{
    do 
    {
        Creature randomCreature = creatureList.getRandomCreature();

        randomCreature.setLevel(player.getLevel());

        Display display;

        int choice = 0;
        int turnCounter = 1;
        bool isCaught = false;

        int damage = 0;
        int scaledPlayerDamage = 0;
        int scaledCreatureDamage = 0;
        
        int exp;
        int gold;

        display.clearScreen();
        std::cout << "You have encountered a " << randomCreature.getName() << "!\n";
        player.addEncounteredCreature(randomCreature);

        while (randomCreature.getHealth() > 0 && player.getHealth() > 0 && !isCaught)
        {
            if (turnCounter <= 1)
            {
                std::cout << "1. Attack\n";
                std::cout << "2. Check Stats\n";
                std::cout << "3. Catch Creature\n";
                std::cout << "4. Run\n";
            }
            else
            {
                std::cout << "1. Attack\n";
                std::cout << "2. Defend\n";
                std::cout << "3. Catch Creature\n";
                std::cout << "4. Run\n";
            }

            std::cout << "What do you do?\n";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                damage = player.doDamage();
                scaledPlayerDamage = randomCreature.takeDamage(damage);

                std::cout << "You did " << scaledPlayerDamage << " damage to " << randomCreature.getName() << ". "
                    << randomCreature.getHealth() << "/" << randomCreature.getTotalHealth() << " left.\n";


                if (randomCreature.getHealth() <= 0) 
                {
                    std::cout << randomCreature.getName() << " has been defeated!\n";
                    exp = randomCreature.giveRandExp();
                    gold = randomCreature.giveRandGold();
                    std::cout << "Congratulations! You received " << exp << " exp and "
                        << gold << " gold!\n";
                    player.gainExp(exp);
                    player.gainGold(gold);
                    break;
                }

                damage = randomCreature.doDamage();
                scaledCreatureDamage = player.takeDamage(damage);
                std::cout << randomCreature.getName() << " did " << scaledCreatureDamage << " damage to you. "
                    << player.getHealth() << "/" << player.getTotalHealth() << " left.\n";


                if (player.getHealth() <= 0) 
                {
                    std::cout << "You have been defeated by " << randomCreature.getName() << "!\n";

                    display.pauseForInput();

                    display.showMenu(player, creatureList);
                    return;
                }

                std::cout << "Press Enter for next turn...";
                std::cin.ignore();  
                std::cin.get();     
                break;
            case 2:
                if (turnCounter <= 1)
                {
                    display.displayCreatureStats(randomCreature);
                }
                else
                {
                    std::cout << "You brace for the enemy's attack, reducing incoming damage!\n";
                    
                    damage = randomCreature.doDamage();
                    scaledCreatureDamage = player.takeReducedDamage(damage);  
                    std::cout << randomCreature.getName() << " did " << scaledCreatureDamage << " damage to you. "
                        << player.getHealth() << "/" << player.getTotalHealth() << " left.\n";
                }

                break;
            case 3:
                isCaught = player.catchCreature(randomCreature);
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid input. Please try again\n";
                continue;
            }
            
            turnCounter++;
        }

        if (player.getHealth() > 0)
        {
            std::cout << "Would you like to fight another creature or return to base to heal?\n";
            std::cout << "1. Fight another\n";
            std::cout << "2. Go to base and heal\n";
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                continue;
            case 2:
                player.heal();
                display.showMenu(player, creatureList);
                return;
            default:
                std::cout << "Invalid input. Returning to the menu.\n";
                display.showMenu(player, creatureList);
                return;
            }
        }
    } while (player.getHealth() > 0);
}