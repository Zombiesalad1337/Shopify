#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

//A vertex is a vector of 3 components(x,y,z)
//value of components range from -1 to +1
class Vertex{
public:
    Vertex(const glm::vec3& pos);

private:
    glm::vec3 pos;
};

class Mesh{
public:
    //vectices are provided in groups of 3 (they form a triangle)
    //3 | numVertices
    Mesh(Vertex* vertices, unsigned int numVertices);
    void Draw();
    virtual ~Mesh();

private:
    //handle for the array object that opengl generates
    GLuint m_vertexArrayObject;    

    enum {
        POSITION_VB, //==0
        NUM_BUFFERS //==1
    };

    //handles for the array buffers that opengl generates
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    //vertexArrayObject is huge, tells how much of it we want to draw
    unsigned int m_drawCount;
};