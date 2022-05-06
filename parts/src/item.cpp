#include "item.h"


Item::Item(std::string name, Category softness, float x, float y) : position{Vertex(x,y)}{
    this->name = name;
    this->softness = softness;
}


//const correctness
std::string Item::getName() const{
    return this->name;
}

Category Item::getSoftness() const{
    return this->softness;
}

Vertex Item::getVertex() const{
    return this->position;
}
