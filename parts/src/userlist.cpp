#include <bits/stdc++.h>
#include "inventory.h"
#include "userlist.h"
#include "utils.h"
#include "item.h"

using namespace std;

UserList::UserList(string filename, Inventory& inventory){
    ifstream fin;
    fin.open(filename);
    string line;

    while (!fin.eof()){
        getline(fin, line);
        if (line.size()){
            listItems.emplace_back(&inventory.items[inventory.mapItems[line]]);
        }
        fin.peek(); //to prevent reading last line twice
    }
    this->sortListItems();
}



void UserList::sortListItems(){
    sort(listItems.begin(), listItems.end(), ItemComparator);
}

void UserList::printListItems(){
    cout << "Name\tCategory" << endl;
    for (auto i : listItems){
        cout << i->getName() << " " << i->getSoftness() << endl;
    }
}