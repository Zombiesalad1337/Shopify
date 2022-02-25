#include "map.h"
#include "utils.h"
#include <fstream>
#include <iostream>

Map::Map(const std::string& filename, float resolution){
    this->resolution = resolution;
    std::ifstream fin;
    fin.open("../src/" + filename);
    std::string line;
    getline(fin,line);

    int count=0;
    while(!fin.eof()){
        getline(fin,line);
        if(line.size()){
            std::vector<float> coords;
            std::vector<std::string> tokens =split(line, ",", "");
            for(int i = 0; i != tokens.size() - 1; ++i){
                auto s = tokens[i];
                float x = stof(s);
                coords.push_back(x);
            }

            polygons.emplace_back(Polygon(coords, tokens.back()));
            count++;
        }
        fin.peek();
    }
}
void Map::printMap(){
    for(auto polygon : this->polygons){
        polygon.printCoords();
    }
    std::cout << std::endl;
}

const std::vector<Polygon>& Map::getPolygons(){
    return polygons;
}

float Map::getResolution(){
    return resolution;
}