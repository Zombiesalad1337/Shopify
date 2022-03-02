#include "vertex.h"
#include <iostream>


Vertex::Vertex(float a,float b){
    this->x=a;
    this->y=b;
}
void Vertex::printVertex() const{
    std::cout << this->x << " " << this->y;
}

float Vertex::getX() const{
    return x;
}

float Vertex::getY() const{
    return y;
}

Vertex Vertex::operator-(const Vertex& v2) const{
    return Vertex(this->getX() - v2.getX(), this->getY() - v2.getY());
}