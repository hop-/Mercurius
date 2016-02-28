#include "frame.hpp"
#include "texture.hpp"
#include "gui_object.hpp"

#include <cassert>

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
    // TODO check SDL_Init(SDL_INIT_VIDEO) == 0 for success
    m_window = SDL_CreateWindow("test title" // TODO title
            , SDL_WINDOWPOS_UNDEFINED
            , SDL_WINDOWPOS_UNDEFINED
            , 800 // TODO should be used Frame::width()
            , 600 // TODO should be used Frame::height()
            , SDL_WINDOW_FULLSCREEN); // TODO window and fullscreen modes
    // TODO check for m_window != 0
    m_renderer = SDL_CreateRenderer(m_window
            , -1
            , SDL_RENDERER_ACCELERATED);
    // TODO check for m_renterer != 0
}

void Frame::clear()
{
    SDL_RenderClear(m_renderer);
}

void Frame::draw(Core::GuiObject* object)
{
    assert(0 != object);
    GuiObject* sdlObject = static_cast<GuiObject*>(object);
    assert(0 != dynamic_cast<GuiObject*>(object));
    assert(0 != m_renderer);
    Texture texture = sdlObject->texture();
    SDL_RenderCopy(m_renderer, texture.texture  // maybe need to be used
            , &(texture.sourceRect)             // SDL_RenderCopyEx(..) to
            , &(texture.destinationRect));      // mirror image left/right
}

void Frame::show()
{
    SDL_RenderPresent(m_renderer);
}

} // namespace Sdl
