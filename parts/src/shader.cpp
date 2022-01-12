#include "shader.h"
#include <iostream>
#include <fstream>

//why static non-member functions? https://stackoverflow.com/questions/8406800/when-should-i-write-the-keyword-static-before-a-non-member-function
//controls visibility here? 
static std::string LoadShader(const std::string& filename);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& filename){
    // creates an empty program object and returns a non-zero value by 
    //which it can be referenced. A program object is an object to which 
    //shader objects can be attached.
    m_program = glCreateProgram();   

    //is the string output of LoadShader is deleted after CreateShader
    //has finished executing?
    m_shaders[0] = CreateShader(LoadShader(filename + "Vertex.glsl"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(filename + "Fragment.glsl"), GL_FRAGMENT_SHADER);

    //attaches all the shaders created to the shader program
    for (unsigned int i = 0; i < NUM_SHADERS; ++i){
        glAttachShader(m_program, m_shaders[i]);
    }
    //Associates a generic vertex attribute index with a named attribute variable
    glBindAttribLocation(m_program, 0, "position");

    glLinkProgram(m_program);
    //Linking can fail, so check for errors
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to Link");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program validation failed");
    
}

Shader::~Shader(){
    //Actually, you could delete them right after linking them to the program, because those shader objects represent just the source code which is no longer needed after the linking is done. The machine code for those shaders is already stored in the Program object at that point. So them hanging around is just waste of some memory.
    for (unsigned int i = 0; i < NUM_SHADERS; ++i){
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}

void Shader::Bind(){
    glUseProgram(m_program);
}

//creates and compiles shader
static GLuint CreateShader(const std::string& text, GLenum shaderType){
    //creates an empty shader object and returns a non-zero value 
    //by which it can be referenced. 
    //A shader object is used to maintain the source code 
    //strings that define a shader.
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0){
        std::cerr << "Error: Shader creation failed" << std::endl;
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    //Replaces the source code in a shader object
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

    return shader;
}



//loads shader file from disk
static std::string LoadShader(const std::string& filename){
    std::ifstream file;
    file.open((filename).c_str());
    std::string output;
    std::string line;

    if (file.is_open()){
        while (file.good()){
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else{
        std::cerr << "ERROR: Failed to load shader" << std::endl;
    }

    return output;
}

//prints error messages encountered while linking and validating
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage){
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else 
        glGetShaderiv(shader, flag, &success);
    
    if (success == GL_FALSE){
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errorMessage << ": " << error << std::endl;
    }
}