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

//map.getPolygons returns a const ref to a vector of polygons
//In map.getPolygons[0].getVertices(), the getVertices() should not
//modify the Polygon at polygons[0] as a const ref is passed
//const correctness tells the compiler that the method getVertices
//doesn't modify the state of the Polygon object
const std::vector<Vertex>& Polygon::getVertices() const{
    return vertices;
}

const std::string& Polygon::getName(){
    return name;
}