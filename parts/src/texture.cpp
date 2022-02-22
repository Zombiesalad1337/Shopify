#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cassert>
#include <iostream>

namespace gfx{
Texture::Texture(const std::string& fileName){
    //stbi_load returns 3 pieces of data
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
    
    if (imageData == NULL){
        std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
    }
    //generates space for 1 texture (opengl stores everything as buffers)
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    //sets texture wrapping for both axes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //sets up minification and magnification
    //linearly interpolates texture if it's smaller or larger than
    //the required size
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //sends texture to the gpu
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    //delete imageData as soon as we have sent everything
    //to opengl
    stbi_image_free(imageData);
}

Texture::~Texture(){
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit){
    //unit can only range from 0 to 31
    assert(unit >= 0 && unit < 32);

    //changes what texture opengl is working with
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

} //namespace gfx