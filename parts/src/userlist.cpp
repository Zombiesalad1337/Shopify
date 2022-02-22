#include "inventory.h"
#include "userlist.h"
#include "utils.h"
#include "item.h"
#include <fstream>
#include <iostream>
#include <algorithm>


UserList::UserList(std::string filename, Inventory& inventory){
    std::ifstream fin;
    fin.open("../src/" + filename);
    std::string line;

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
    std::sort(listItems.begin(), listItems.end(), ItemComparator);
}

void UserList::printListItems(){
    std::cout << "Name\tCategory" << std::endl;
    for (auto i : listItems){
        std::cout << i->getName() << " " << i->getSoftness() << std::endl;
    }
}