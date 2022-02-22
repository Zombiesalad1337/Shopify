#pragma once
#include <GL/glew.h>
#include <string>

namespace gfx{
//loads texture from the disk
class Texture{
public:
    Texture(const std::string& fileName);

    //can bind multiple textures
    //unit tells which texture to bind
    void Bind(unsigned int unit);
    virtual ~Texture();
private:
    //handle
    GLuint m_texture;
};

} //namespace gfx