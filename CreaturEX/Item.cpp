#include "Item.h"

Item::Item(std::string itemName, int itemPrice)
	: name(itemName), price(itemPrice) 
{	
}


std::string Item::getName() const
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


std::vector<Item> Item::createItemDatabase() 
{
	return 
	{
		Item("Hexball", 15),
		Item("Health Potion I", 20),
		Item("Health Potion II", 35),
		Item("Attack Potion", 30),
		Item("Defense Potion", 25),
		Item("Revive", 50)
	};
}