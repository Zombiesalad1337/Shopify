#pragma once
#include <string>
#include <SDL2/SDL.h>


class Display{
public:
    Display(int width, int height, const std::string& name);
    ~Display();
    void Clear(float r, float g, float b, float a);
    bool IsClosed();
    void Update();

private:
    bool m_isClosed;
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};