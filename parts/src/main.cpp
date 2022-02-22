#include "item.h"
#include "inventory.h"
#include "userlist.h"
#include "map.h"
#include <vector>
#include <string>
#include <iostream>


int main(){
    std::vector<std::string> names = {"frooti", "rice", "eggs"};
    std::vector<Category> cats = {Category::medium, Category::hard, Category::soft};
    
    std::vector<Item> items;
    for (int i = 0; i != names.size(); ++i){
        items.emplace_back(Item(names[i], cats[i]));
    }

    // for (Item i : items){
    //     cout << i.getName() << " ";
    //     cout << i.getSoftness() << endl; 
    // }
    // sortItems(items);
    // for (Item i : items){
    //     cout << i.getName() << " ";
    //     cout << i.getSoftness() << endl; 
    // }

    Inventory inventory("inventory.csv");
    inventory.printInventory();
    std::cout << std::endl << std::endl;

    UserList userList("userlist.txt", inventory);
    userList.printListItems();

    Map map("../src/map.csv");
    map.printMap();
    return 0;
}
