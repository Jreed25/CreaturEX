#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

class Item
{
private:
	std::string name;
	int price;


public:
	Item(std::string itemName, int itemPrice);

	static std::vector<Item> createItemDatabase();

	std::string getName() const;
	int getPrice() const;

	void setPrice(int newPrice);
};

#endif
