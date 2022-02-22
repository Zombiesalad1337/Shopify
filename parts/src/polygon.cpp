#include "polygon.h"
#include "vertex.h"
#include <iostream>

Polygon::Polygon(std::vector<float>& coords, std::string name){
    for (int i = 0; i < coords.size() / 2; ++i){
        this->vertices.push_back(Vertex(coords[2 * i], coords[2 * i + 1]));
    }
    this->name = name;
}
// string polygon::getname() {
//     return this->name;
// }
void Polygon::printCoords(){
    for(auto vertex : this->vertices){
        vertex.printVertex();
        std::cout << " || ";
    }
    std::cout << std::endl;
}