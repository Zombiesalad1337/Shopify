#pragma once

class Vertex{
private : 
    float x;
    float y;
public: 
    Vertex(float a,float b);
    void printVertex() const;
    
    //no need for const correctness here??? no errors without it
    float getX() const;
    float getY() const;

    Vertex operator-(const Vertex& v2) const;
};