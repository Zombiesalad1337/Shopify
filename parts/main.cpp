#include <bits/stdc++.h>
#include "item.h"
using namespace std;

bool ItemComparator(const Item& item1, const Item& item2){
    return item1.getSoftness() < item2.getSoftness();
}

void sortItems(vector<Item>& items){
    sort(items.begin(), items.end(), ItemComparator);
}

int main(){
    vector<string> names = {"frooti", "rice", "eggs"};
    vector<Category> cats = {Category::medium, Category::hard, Category::soft};
    
    vector<Item> items;
    for (int i = 0; i != names.size(); ++i){
        items.emplace_back(Item(names[i], cats[i]));
    }

    for (Item i : items){
        cout << i.getName() << " ";
        cout << i.getSoftness() << endl; 
    }
    sortItems(items);
    for (Item i : items){
        cout << i.getName() << " ";
        cout << i.getSoftness() << endl; 
    }
 
    
    return 0;
}


//g++ -c item.cpp -o item.o && g++ -c main.cpp -o main.o && g++ item.o main.o -o main.out && ./main.out
//set up cmake 