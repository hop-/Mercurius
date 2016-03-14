#ifndef _SDL_FRAME_HPP_
#define _SDL_FRAME_HPP_

#include "core/frame.hpp"

#include <SDL2/SDL.h>

namespace Sdl
{

class Frame
    : public Core::Frame
{
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

public:
    ~Frame();
    void init();
    void clear();

    void* renderer() const
    {
        return m_renderer;
    }

private:
    void draw(const Core::GuiObject* object);
    void show();
};

} // namespace Sdl

#endif //_SDL_FRAME_HPP_
