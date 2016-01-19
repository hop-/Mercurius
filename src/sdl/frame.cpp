#include "frame.hpp"

namespace Sdl
{
    

Frame::~Frame()
{
    SDL_DestroyWindow(m_window);
    m_window = 0;
    SDL_DestroyRenderer(m_renderer);
    m_renderer = 0;
}

void Frame::init()
{
    // TODO check for possibility of init
    m_window = SDL_CreateWindow("test title"
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , 800
            , 600
            , SDL_WINDOW_SHOWN);
    // TODO check for m_window != 0
    m_renderer = SDL_CreateRenderer(m_window
            , -1
            , SDL_RENDERER_ACCELERATED);
    // TODO check for m_renterer != 0
}


} // namespace Sdl
