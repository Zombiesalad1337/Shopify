#include "display.h"
#include <iostream>
#include <GL/glew.h>

namespace gfx{

Display::Display(int width, int height, const std::string& name){

    SDL_Init(SDL_INIT_EVERYTHING);
    
    //color depth, 2^8 = 256 shades of r, g, b, a
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    //size for a single pixel, 8 * 4
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    //we need two buffers, one that is currently being displayed
    //and one that is opengl drawing on.
    //when drawing is finished, then both buffers are swapped
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //c_str() since opencl is a C library (string not supported)
    //SDL_WINDOW_OPENGL tells sdl that the window contents will
    //be handled by opengl?
    m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_OPENGL);
    
    //OpenGL context, which is essentially a state machine that 
    //stores all data related to the rendering of your application. 
    //When your application closes, the OpenGL context is 
    //destroyed and everything is cleaned up.

    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if (status != GLEW_OK){
        std::cerr << "ERROR Initializing Glew" << std::endl;
    }
    m_isClosed = false;
}

Display::~Display(){
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a){
    //sets the clear color
    glClearColor(r, g, b, a);
    //clears the window with the clear color set above
    glClear(GL_COLOR_BUFFER_BIT);
}

bool Display::IsClosed(){
    return m_isClosed;
}

//the window created also needs to handle events such as quit,
//maximize... If not handled, then OS thinks the application
//is not responding. 
void Display::Update(){
    //swaps the two buffers
    SDL_GL_SwapWindow(m_window);    

    SDL_Event e;

    //process currently pending events 
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            m_isClosed = true;
        }
    }
}

} //namespace gfx