#ifndef SHOP_H
#define SHOP_H

#include "Item.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <vector>


class Player;

class Shop
{
private:
	std::vector<Item> inventory;

public:
	Shop();

	void displayShopInventory(Player& player);

	void buyItem(Player& player, int itemIndex);
	void sellItem(Player& player, int itemIndex);
	void addItemToShop(const Item& item);

	void exitShop() const;
};

#endif