#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

using namespace std;

class Item
{
private:
	string name;
	int price;
	vector<Item> items;

public:
	// Constructor
	Item(string itemName, int itemPrice);


	// Getters
	string getName() const;
	int getPrice() const;



	// Setters
	void setPrice(int newPrice);


};


#endif
