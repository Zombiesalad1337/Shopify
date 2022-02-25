#pragma once

class Vertex{
private : 
    float x;
    float y;
public: 
    Vertex(float a,float b);
    void printVertex();
    
    //no need for const correctness here??? no errors without it
    const float& getX();
    const float& getY();
};