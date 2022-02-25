#pragma once
#include "vertex.h"
#include <vector>
#include <string>


class Polygon{
private:
    std::vector<Vertex> vertices;
    std::string name;
public:
    Polygon(std::vector<float>& coords, std::string name);
    void printCoords();
    const std::vector<Vertex>& getVertices() const;
    const std::string& getName();
};