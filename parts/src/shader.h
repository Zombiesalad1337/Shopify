#pragma once
#include <string>
#include <GL/glew.h>

//loads the shader file, builds it and sends the built file 
//to the gpu
class Shader{
public:
    Shader(const std::string& filename);

    //sets the gpu in a state so that it uses the shaders
    //provided by this shader class
    void Bind();


    virtual ~Shader();

private:
    static const unsigned int NUM_SHADERS = 2;

    //handle to keep track of the shader program
    GLuint m_program;

    //handles for different shaders
    GLuint m_shaders[NUM_SHADERS];
};