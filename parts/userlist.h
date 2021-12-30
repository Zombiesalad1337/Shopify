#pragma once
#include <bits/stdc++.h>
#include "inventory.h"
#include "item.h"

using namespace std;

class UserList{
private:
    //item reference since actual item objects are stored in a vector
    //of the inventory object
    vector<Item*> listItems;
public:
    UserList(string filename, Inventory& inventory);
    void sortListItems();
    void printListItems();
};