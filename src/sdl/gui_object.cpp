#include "gui_object.hpp"
#include "frame.hpp"
#include "texture.hpp"

#include <core/gui.hpp>
#include <core/frame.hpp>
#include <core/position.hpp>

#include <SDL2/SDL_image.h>

#include <cassert>

namespace Sdl
{

void GuiObject::init()
{
    assert(0 != parent());
    assert(0 != parent<Core::Gui>()->frame());
    SDL_Renderer* renderer = static_cast<SDL_Renderer*>(
            parent<Core::Gui>()->frame()->renderer());
    assert(0 != renderer);
    m_texture.texture = IMG_LoadTexture(renderer,
            textureLocation().c_str());
    assert(m_texture.texture);
    m_texture.sourceRect = SDL_Rect{0, 0, width(), height()};
    m_texture.destinationRect = SDL_Rect{0, 0
        , int(width() * scaleFactor())
        , int(height() * scaleFactor())};
    assert(0 != subject());
}

void GuiObject::onNotify()
{
    Core::GuiObject::onNotify();
    updateDestRect();
    changeSourceRect();
}

void GuiObject::updateDestRect()
{
    //Core::Position objectPosition = m_textureRederer->objectPosition();
    m_texture.destinationRect.x = x();
    m_texture.destinationRect.y = y();
}

void GuiObject::changeSourceRect()
{
    m_texture.sourceRect.x = width() * state();
}

GuiObject::GuiObject(const std::string& texture)
    : Core::GuiObject()
{
    setTextureLocation(texture);
}

} // namespace Sdl
