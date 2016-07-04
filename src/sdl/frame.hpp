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
    Frame();
    virtual ~Frame();
    void init();
    void clear();

    void* renderer() const
    {
        return m_renderer;
    }

private:
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

private:
    void draw(const Core::GuiObject* object);
    void show();
    void correctResolution();

private:
    SDL_Rect* mapToFrame(SDL_Rect&, int);
    SDL_Rect* mapToActive(SDL_Rect&, int);
//    SDL_Rect* mapToList(SDL_Rect&, int);
//    SDL_Rect* mapToGrid(SDL_Rect&, int);
};

} // namespace Sdl

#endif //_SDL_FRAME_HPP_
