/* Start with simple menu and combat system
* Character Creation
*/
/* Class: Pokemon(Name, Health, Later on:(Catch rate, ))
*  Class: User(Later on: (Inventory))
* Menu:
*
  /* 1. Explore = Left, Right, Straight
*	 Random Pokemon (or nothing) then choice to attack or try to catch
*		Catch = Throw pokeball certain chance to catch depending on pokemon given multiple shots until out of pokeballs
*
* 2. Bestiary
*       Listing all possible pokemone encounters
*
* 3. (Later on: Shop)
*
* 4. Quit Program
*/

/* Later on things
* Shop
* Inventory
*/


// Headers
#include "Display.h"
#include "Player.h"
#include "Creature.h"
#include "SaveManager.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Global variables

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator


    // Choice Variables
    int start_choice = 0;

    // Classes
    Player player;
    Display display;
    CreatureList creatureList;
    Save save;

    while (start_choice != 3)
    {
        // Game Start
        system("cls");
        cout << "This is CreatureX.\n";
        cout << "1. Character Creation\n";
        cout << "2. Load Character\n";
        cout << "3. Quit Game\n";
        cout << "Enter your choice: \n";
        cin >> start_choice;


        // Case for start choice
        switch (start_choice) {
        case 1:

            player.allocateStatPoints(player, creatureList);
            break;
        case 2:

            save.loadGame(player);
            display.showMenu(player, creatureList);
            break;
        case 3:

            exit(EXIT_FAILURE);
            break;
        default:

            cout << "Invalid input. Try Again.\n\n";
            break;


        }
    }



    return 0;
}