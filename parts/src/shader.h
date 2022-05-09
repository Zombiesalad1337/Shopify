#pragma once
#include <string>
#include <GL/glew.h>
#include "transform.h"

namespace gfx{
//loads the shader file, builds it and sends the built file 
//to the gpu
class Shader{
public:
    Shader(const std::string& filename);

    //sets the gpu in a state so that it uses the shaders
    //provided by this shader class
    void Bind();

    //updates the transform uniform
    void Update(const Transform& transform);

    virtual ~Shader();

    void setColor(const glm::vec4& color);

private:
    static const unsigned int NUM_SHADERS = 2;

    enum {
        TRANSFORM_U,
        COLOR_U,
        
        NUM_UNIFORMS
    };
    //handle to keep track of the shader program
    GLuint m_program;

    //handles for different shaders
    GLuint m_shaders[NUM_SHADERS];

    //handles for uniform variables
    GLuint m_uniforms[NUM_UNIFORMS];
};


} //namespace gfx
