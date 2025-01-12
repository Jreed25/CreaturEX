#include "Shop.h"
#include "Item.h"
#include "Player.h"
#include <vector>



Shop::Shop() {
	addItemToShop(Item("Hexball", 15));
	addItemToShop(Item("Health Potion I", 20));
	addItemToShop(Item("Health Potion II", 35));
	addItemToShop(Item("Attack Potion", 30));
	addItemToShop(Item("Defense Potion", 25));
	addItemToShop(Item("Revive", 50));
}

void Shop::displayShopInventory(Player& player)
{
	Shop shop;
	bool inShop = true;
	int choice = 0;
	int itemIndex;


	while (inShop)
	{
		cout << "\n---- Welcome to Creatara Shop! ----\n";
		cout << "Items for Sale: \n";
		for (size_t i = 0; i < inventory.size(); ++i)
		{
			cout << i + 1 << ". " << inventory[i].getName() << " - " <<
				inventory[i].getPrice() << "G" << endl;
		}

		cout << "\n1. Buy Item\n";
		cout << "2. Sell Item\n";
		cout << "3. Exit Shop\n";
		cin >> choice;

		switch (choice)
		{
		case 1:

			cout << "Enter the item number to buy: ";
			cin >> itemIndex;
			shop.buyItem(player, itemIndex - 1);
			break;
		case 2:

			shop.sellItem(player, -1);
			break;
		case 3:

			shop.exitShop();
			inShop = false;
			break;

		default:
			cout << "Invalid choice.\n";

		}

		cout << "\nPlayer Stats:\n";
		cout << "Gold: " << player.getGold() << "\n";
		player.displayInventory();
	}
}


void Shop::buyItem(Player& player, int itemIndex)
{
	if (itemIndex < 0 || itemIndex >= static_cast<int>(inventory.size()))
	{
		cout << "Invalid item selection.\n";
		return;
	}

	Item& selectedItem = inventory[itemIndex];
	if (player.getGold() >= selectedItem.getPrice())
	{
		player.subtractGold(selectedItem.getPrice());
		player.addItem(selectedItem);
		cout << "You bought a " << selectedItem.getName() << endl;
	}
	else
	{
		cout << "You don't have enough gold. \n";
	}
}


void Shop::sellItem(Player& player, int itemIndex)
{
	if (player.isInventoryEmpty())
	{
		cout << "Your inventory is empty. Nothing to sell. \n";
		return;
	}

	player.displayInventory();

	cout << "Enter the name of the item you want to sell: ";
	cin.ignore();
	string itemName;
	getline(cin, itemName);

	if (player.hasItem(itemName))
	{

		int sellPrice = 0;
		bool foundItemInShop = false;

		for (const auto& shopItem : inventory)
		{
			if (shopItem.getName() == itemName)
			{
				sellPrice = (shopItem.getPrice() - (2 * (shopItem.getPrice() / 5)));
				foundItemInShop = true;
				break;
			}
		}

		if (foundItemInShop && sellPrice > 0)
		{
			player.removeItem(itemName);
			player.gainGold(sellPrice);
			cout << "You sold " << itemName << " for " << sellPrice << "G. " << endl;
		}
		else
		{
			cout << "Item not found in shop.\n";
		}
	}
	else
	{
		cout << "You dont have " << itemName << " in your inventory.\n";

	}

}

void Shop::addItemToShop(const Item& item) {
	inventory.push_back(item);
}

void Shop::exitShop() const
{
	cout << "Thank you for visiting the shop!\n";
}