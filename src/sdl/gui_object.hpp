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
    GuiObject(const std::string&);

public:
    void init();
    void onNotify();

    Texture texture() const
    {
        return m_texture;
    }

private:
    void updateDestRect();
    void updateDirection();
    void changeSourceRect();
};

} // namespace Sdl

#endif //_SDL_GUI_OBJECT_HPP_
