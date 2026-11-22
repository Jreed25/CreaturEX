#include "Item.h"
#include "Player.h"
#include "Shop.h"

#include <vector>

Shop::Shop() 
	: inventory(Item::createItemDatabase())
{}

void Shop::displayShopInventory(Player& player)
{
	bool inShop = true;
	int choice = 0;
	int itemIndex;


	while (inShop)
	{
		std::cout << "\n---- Welcome to Creatara Shop! ----\n";
		std::cout << "Items for Sale: \n";
		for (size_t i = 0; i < inventory.size(); ++i)
		{
			std::cout << i + 1 << ". " << inventory[i].getName() << " - " <<
				inventory[i].getPrice() << "G" << '\n';
		}

		std::cout << "\n1. Buy Item\n";
		std::cout << "2. Sell Item\n";
		std::cout << "3. Exit Shop\n";
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "Enter the item number to buy: ";
			std::cin >> itemIndex;
			buyItem(player, itemIndex - 1);
			break;
		case 2:
			sellItem(player, -1);
			break;
		case 3:
			exitShop();
			inShop = false;
			break;
		default:
			std::cout << "Invalid choice.\n";
		}

		std::cout << "\nPlayer Stats:\n";
		std::cout << "Gold: " << player.getGold() << "\n";
		player.displayInventory();
	}
}


void Shop::buyItem(Player& player, int itemIndex)
{
	if (itemIndex < 0 || itemIndex >= static_cast<int>(inventory.size()))
	{
		std::cout << "Invalid item selection.\n";
		return;
	}

	Item& selectedItem = inventory[itemIndex];
	if (player.getGold() >= selectedItem.getPrice())
	{
		player.subtractGold(selectedItem.getPrice());
		player.addItem(selectedItem);
		std::cout << "You bought a " << selectedItem.getName() << '\n';
	}
	else
	{
		std::cout << "You don't have enough gold. \n";
	}
}


void Shop::sellItem(Player& player, int itemIndex)
{
	if (player.isInventoryEmpty())
	{
		std::cout << "Your inventory is empty. Nothing to sell. \n";
		return;
	}

	player.displayInventory();

	std::cout << "Enter the name of the item you want to sell: ";
	std::cin.ignore();
	std::string itemName;
	std::getline(std::cin, itemName);

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
			std::cout << "You sold " << itemName << " for " << sellPrice 
				<< "G. " << '\n';
		}
		else
		{
			std::cout << "Item not found in shop.\n";
		}
	}
	else
	{
		std::cout << "You dont have " << itemName << " in your inventory.\n";
	}
}

void Shop::addItemToShop(const Item& item) 
{
	inventory.push_back(item);
}

void Shop::exitShop() const
{
	std::cout << "Thank you for visiting the shop!\n";
}