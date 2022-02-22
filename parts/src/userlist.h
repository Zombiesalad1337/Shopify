#pragma once
#include "inventory.h"
#include "item.h"
#include <vector>
#include <string>

class UserList{
private:
    //item reference since actual item objects are stored in a vector
    //of the inventory object
    std::vector<Item*> listItems;
public:
    UserList(std::string filename, Inventory& inventory);
    void sortListItems();
    void printListItems();
};