#include "Item.h"

#include <vector>

// Item class implementation
Item::Item(string itemName, int itemPrice)
	: name(itemName), price(itemPrice) {}


// Getter/setter********
//**********************
string Item::getName() const
{
	return name;
}

int Item::getPrice() const
{
	return price;
}

void Item::setPrice(int newPrice)
{
	price = newPrice;
}


// Item database
vector<Item> createItemDatabase() {
	return {
		Item("Hexball", 15),
		Item("Health Potion I", 20),
		Item("Health Potion II", 35),
		Item("Attack Potion", 30),
		Item("Defense Potion", 25),
		Item("Revive", 50),
	};
}