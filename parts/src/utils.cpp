#include "utils.h"
#include <boost/tokenizer.hpp>

std::vector<std::string> split(std::string s, const char* sep1, const char* sep2)
{
    std::vector<std::string> tokens;
    boost::char_separator<char> sep(sep1, sep2);
    boost::tokenizer<boost::char_separator<char> > tok(s, sep);
    for(auto i = tok.begin(); i!=tok.end(); ++i)
        tokens.emplace_back(*i);
    return tokens;
}

bool ItemComparator(const Item* item1, const Item* item2){
    return item1->getSoftness() < item2->getSoftness();
}


float crossProduct(const Vertex& v1, const Vertex& v2){
    return v1.getX() * v2.getY() -  v1.getY() * v2.getX();   
}


bool isPointInTriangle(const Vertex& p, const Vertex& a, const Vertex& b, const Vertex& c){
    
    Vertex ab = b - a;
    Vertex bc = c - b;
    Vertex ca = a - c;

    Vertex ap = p - a;
    Vertex bp = p - b;
    Vertex cp = p - c;

    float cross1 = crossProduct(ab, ap);
    float cross2 = crossProduct(bc, bp);
    float cross3 = crossProduct(ca, cp);

    //point lies outside triangle
    if (cross1 > 0.0f || cross2 > 0.0f || cross3 > 0.0f){
        return false;
    }
    //when point lines inside triangle or on an edge
    return true;
}

//for triangulate
//https://stackoverflow.com/questions/12276675/modulus-with-negative-numbers-in-c
int mod(int k, int n) {
    return ((k %= n) < 0) ? k+n : k;
}