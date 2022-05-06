#pragma once
#include <string>
#include "vertex.h"
//if I include <string> here and again in main.cpp, then is it included twice?
//won't compile if <string> is excluded here
//standard libs already contain #pragma once?

enum Category {
    hard, medium, soft
};

class Item {
private:
    std::string name;
    Category softness;
    Vertex position;

public:
    Item(std::string name, Category softness, float x, float y);
    std::string getName() const;
    Category getSoftness() const;
    Vertex getVertex() const;
};
