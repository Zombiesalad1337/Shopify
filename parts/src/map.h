#pragma once
#include "polygon.h"
#include <vector>


class Map{
private:
    std::vector<Polygon> polygons;
    float resolution;
public:
    Map(const std::string& filename, float resolution = 0.25);
    void printMap();
    const std::vector<Polygon>& getPolygons();
};