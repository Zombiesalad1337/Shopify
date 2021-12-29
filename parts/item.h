#pragma once
#include <string>
//if I include <string> here and again in main.cpp, then is it included twice?
//won't compile if <string> is excluded here
using namespace std;

enum Category {
    hard, medium, soft
};

class Item {
private:
    string name;
    Category softness;

public:
    Item(string name, Category softness);
    string getName();
    Category getSoftness();
};