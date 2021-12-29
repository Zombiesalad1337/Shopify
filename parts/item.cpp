#include "item.h"
using namespace std;

Item::Item(string name, Category softness){
    this->name = name;
    this->softness = softness;
}

string Item::getName(){
    return this->name;
}

Category Item::getSoftness(){
    return this->softness;
}