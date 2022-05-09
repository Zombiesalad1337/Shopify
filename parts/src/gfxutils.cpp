#include "gfxutils.h"
#include "mesh.h"
namespace gfx{


void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numSides, std::vector<std::unique_ptr<Mesh>>& circleMesh){

    int numVertices = numSides + 2;

    GLfloat tau = 2.0f * M_PI;

    Vertex* triangleVerticesArray = new Vertex[numVertices]; 
    
    triangleVerticesArray[0] = gfx::Vertex(glm::vec3(0 ,0, 0));

    for (int i = 1; i < numVertices; ++i){
        float xCoord = x + (radius * cos(i * tau / numSides));
        float yCoord = y + (radius * sin(i * tau / numSides));

        triangleVerticesArray[i] = gfx::Vertex(glm::vec3(xCoord, yCoord, 0));
    }

    circleMesh.emplace_back(new Mesh(triangleVerticesArray, numVertices, GL_TRIANGLE_FAN));  
    
}

} //namespace gfx
