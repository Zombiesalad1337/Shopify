#include "item.h"
#include "inventory.h"
#include "utils.h"
#include <fstream>
#include <iostream>


Inventory::Inventory(std::string filename){
    std::map<std::string, Category> catMap;
    catMap["hard"] = Category::hard;
    catMap["medium"] = Category::medium;
    catMap["soft"] = Category::soft;

    std::ifstream fin;
    fin.open("../src/" + filename);
    std::string line;
    getline(fin, line);

    int count = 0;
    while (!fin.eof()){
        getline(fin, line);
        //first line contains headers, read from 2nd line
        if (line.size()){
            if (line[0] == '#') continue;
            if (!line.compare("EOF")) break;
            std::cout << line << std::endl;
            std::vector<std::string> tokens = split(line, ",", "");
            items.emplace_back(Item(tokens[0], catMap[tokens[1]], stof(tokens[2]), stof(tokens[3])));
            mapItems[tokens[0]] = count;
            count++;
        }
        fin.peek(); //to prevent reading last line twice
    }
}

void Inventory::printInventory(){
    std::cout << "Name\tCategory" << std::endl;
    for (Item i : items){
        std::cout << i.getName() << "  " << i.getSoftness() << std::endl;
    }
}
