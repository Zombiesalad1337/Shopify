#include "vertex.h"
#include <iostream>


Vertex::Vertex(float a,float b){
    this->x=a;
    this->y=b;
}
void Vertex::printVertex(){
    std::cout << this->x << " " << this->y;
}