#include "item.h"
#include "inventory.h"
#include "utils.h"
#include <bits/stdc++.h>
using namespace std;


Inventory::Inventory(string filename){
    map<string, Category> catMap;
    catMap["hard"] = Category::hard;
    catMap["medium"] = Category::medium;
    catMap["soft"] = Category::soft;

    ifstream fin;
    fin.open(filename);
    string line;
    getline(fin, line);

    int count = 0;
    while (!fin.eof()){
        getline(fin, line);
        //first line contains headers, read from 2nd line
        if (line.size()){
            vector<string> tokens = split(line, ",", "");
            items.emplace_back(Item(tokens[0], catMap[tokens[1]]));
            mapItems[tokens[0]] = count;
            count++;
        }
        fin.peek(); //to prevent reading last line twice
    }
}

void Inventory::printInventory(){
    cout << "Name\tCategory" << endl;
    for (Item i : items){
        cout << i.getName() << "  " << i.getSoftness() << endl;
    }
}