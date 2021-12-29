#include "item.h"
using namespace std;

Item::Item(string name, Category softness){
    this->name = name;
    this->softness = softness;
}


//const correctness
string Item::getName() const{
    return this->name;
}

Category Item::getSoftness() const{
    return this->softness;
}