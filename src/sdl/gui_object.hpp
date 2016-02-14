#ifndef _SDL_GUI_OBJECT_HPP_
#define _SDL_GUI_OBJECT_HPP_

#include "texture.hpp"

#include <core/gui_object.hpp>

#include <SDL2/SDL.h>

namespace Sdl
{

class GuiObject
    : public Core::GuiObject
{
    Texture m_texture;

public:
    void init();
    void onNotify();

    inline Texture texture() const
    {
        return m_texture;
    }
};

} // namespace Sdl

#endif //_SDL_GUI_OBJECT_HPP_
