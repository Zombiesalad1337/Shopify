#include "mesh.h"

namespace gfx{

Vertex::Vertex(const glm::vec3& pos, const glm::vec2& texCoord){
    this->pos = pos;
    this->texCoord = texCoord;
}

Vertex::Vertex(const glm::vec3& pos){
    this->pos = pos;
}

Vertex::Vertex(){
    this->pos = glm::vec3(0, 0, 0);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, GLuint type){
    this->type = type;
    //currently drawing for per vertex basis, other ways to draw exist
    m_drawCount = numVertices;

    //creates vertex array object names
    //the second parameter is an array, using uint now since we're
    //only creating one
    //stores the handles for vertex array objects in the second parameter
    //array
    glGenVertexArrays(1, &m_vertexArrayObject);

    //after binding, any operation that affects the vertex array
    //object will affect the one which is bound
    glBindVertexArray(m_vertexArrayObject);

    //opengl refers to data on the gpu as buffers (any block of data)
    //generates blocks of data on the gpu that we can write to
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    //any opengl operation that affects a buffer will now affect
    //this one
    //buffer is just a block of data, can mean anything
    //the flag tells opengl to interpret the buffer data as an array
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);


    //sends the vertices data to the gpu
    //last param is usage. Specifies the expected usage pattern of the data store.
    //usage is a hint to the GL implementation as to how a buffer object's data 
    //store will be accessed. This enables the GL implementation to make more 
    //intelligent decisions that may significantly impact buffer object performance. 
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    //Specifies the index of the generic vertex attribute to be enabled or disabled.
    glEnableVertexAttribArray(0);

    //define an array of generic vertex attribute data
    //gpu expects a sequential array of data when rendering vertices(x,y,z floats)
    //the vertex class may contain attributes like pos and color.
    //the array would look like pos,color,pos,color...
    //we need to skip all the color attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);

    //for texture
    //enables vertex texture attribute
    // glEnableVertexAttribArray(1);
    //tells how to read the second(texCoord) attribute
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *)(3 * sizeof(GL_FLOAT)));

    //releases the bind/operations dont't affect any vertex array 


    switch(type){
        case GL_LINES:
            break;
        case GL_TRIANGLES:
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *)(3 * sizeof(GL_FLOAT)));
            break;
        default:
            break;
    }

    glBindVertexArray(0);
}


Mesh::~Mesh(){
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}


//draws the mesh data that was sent to the gpu
void Mesh::Draw(){
    glBindVertexArray(m_vertexArrayObject);

    //to draw an array of data
    //p1 - tells that kind of primitive to render
    //p2 - starting index
    //p3 - number of indices to render
    //in this case arr[0..m_drawcount - 1] will be rendered
    glDrawArrays(type, 0, m_drawCount); 

    glBindVertexArray(0);
}

} //namespace gfx