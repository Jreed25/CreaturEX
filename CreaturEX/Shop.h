#ifndef SHOP_H
#define SHOP_H

#include "Player.h"
#include "Item.h"
#include <vector>
#include <string>
#include <iostream>



class Player;

class Shop
{
private:
	vector<Item> inventory;

public:
	Shop();

	// Display
	void displayShopInventory(Player& player);

	// Actions
	void buyItem(Player& player, int itemIndex);
	void sellItem(Player& player, int itemIndex);
	void addItemToShop(const Item& item);

	void exitShop() const;




};

#endif