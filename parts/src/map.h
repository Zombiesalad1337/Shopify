#pragma once
#include "polygon.h"
#include <vector>


class Map{
private:
    std::vector<Polygon> polygons;
public:
    Map(std::string filename);
    void printMap();
};