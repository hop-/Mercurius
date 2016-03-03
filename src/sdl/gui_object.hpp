#ifndef _SDL_GUI_OBJECT_HPP_
#define _SDL_GUI_OBJECT_HPP_

#include "texture.hpp"

#include <core/gui_object.hpp>

#include <SDL2/SDL.h>

namespace Core
{
class TextureRenderer;
}

namespace Sdl
{

class GuiObject
    : public Core::GuiObject
{
    Texture m_texture;
    const Core::TextureRenderer* m_textureRederer;

public:
    GuiObject(const std::string&);

public:
    void init();
    void onNotify();

    inline Texture texture() const
    {
        return m_texture;
    }

private:
    void changeSourceRect(int state);
};

} // namespace Sdl

#endif //_SDL_GUI_OBJECT_HPP_
