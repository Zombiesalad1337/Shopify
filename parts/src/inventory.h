#pragma once
#include "item.h"
#include <vector>
#include <string>
#include <map>


class Inventory{
private:
    std::vector<Item> items;
    //map<string, int> seems better, since Item& can cause scope related errors?
    // map<string, Item&> mapItems;
    std::map<std::string, int> mapItems;

    //include 2D map object
    friend class UserList;
public:
    Inventory(std::string filename);
    void printInventory();
};