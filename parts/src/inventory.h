#pragma once
#include <bits/stdc++.h>
#include "item.h"
using namespace std;

class Inventory{
private:
    vector<Item> items;
    //map<string, int> seems better, since Item& can cause scope related errors?
    // map<string, Item&> mapItems;
    map<string, int> mapItems;

    //include 2D map object
    friend class UserList;
public:
    Inventory(string filename);
    void printInventory();
};