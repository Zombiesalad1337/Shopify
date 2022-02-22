#include "item.h"


Item::Item(std::string name, Category softness){
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