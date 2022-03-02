#include "polygon.h"
#include "vertex.h"
#include "utils.h"
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
//source - https://github.com/twobitcoder101/Polygon-Triangulation/blob/main/TriangulatePolygon.cs
std::vector<Vertex> Polygon::Triangulate() const{
    std::vector<Vertex> triangleVertices;

    if (vertices.size() == 0){
        std::cout << "Polygon has no vertices" << std::endl;
        return triangleVertices;
    }
    if (vertices.size() < 3){
        std::cout << "Polygon must have at least 3 vertices" << std::endl;
    }

    std::vector<int> indexList;
    for (int i = 0; i < vertices.size(); ++i){
        indexList.emplace_back(i);
    } 
    std::cout << "index list size: " << indexList.size() << std::endl;
    std::cout << (10 % 9) << std::endl;

    std::cout << "triangulate 1" << std::endl;
    while (indexList.size() > 3){
        std::cout << "triangulate 2" << std::endl;
        for (int i = 0; i < indexList.size(); ++i){

            int a = indexList[i];
            int b = indexList[mod(i - 1, indexList.size())];
            int c = indexList[mod(i + 1, indexList.size())];

            std::cout << b << " " << a << " " << c << std::endl;

            Vertex va = vertices[a];
            Vertex vb = vertices[b];
            Vertex vc = vertices[c];
            
            Vertex va2vb = vb - va;
            Vertex va2vc = vc - va;

            //test for reflex vertex
            if (crossProduct(va2vb, va2vc) < 0.0f){
                continue;
            }

            bool isEar = true;

            std::cout << "triangulate 3" << std::endl;
            for (int j = 0; j < vertices.size(); ++j){
                if (j == a || j == b || j == c){
                    continue;
                }

                Vertex p = vertices[j];

                if (isPointInTriangle(p, vb, va, vc)){
                    isEar = false;
                    break;
                }
            }
            
            if (isEar){
                std::cout << "emplaced" << std::endl;
                triangleVertices.emplace_back(vertices[b]);
                triangleVertices.emplace_back(vertices[a]);
                triangleVertices.emplace_back(vertices[c]);

                std::cout << b << " " << a << " " << c << std::endl;
                indexList.erase(indexList.begin() + i);
                std::cout << indexList.size() << std::endl;
                break;
            }
        }
    }

    std::cout << "triangulate 4" << std::endl;
    triangleVertices.emplace_back(vertices[indexList[0]]);
    triangleVertices.emplace_back(vertices[indexList[1]]);
    triangleVertices.emplace_back(vertices[indexList[2]]);

    return triangleVertices;
}