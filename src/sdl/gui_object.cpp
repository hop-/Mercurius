#include "frame.hpp"
#include "gui_object.hpp"
#include "texture.hpp"

#include <core/gui.hpp>
#include <core/frame.hpp>
#include <core/components.hpp>
#include <core/rectangle.hpp>

#include <SDL2/SDL_image.h>

#include <cassert>

namespace Sdl
{

namespace  {

SDL_Rect toSDL_Rect(const Core::Rectangle& rect)
{
    return SDL_Rect{int(rect.position().x())
        , int(rect.position().y())
        , int(rect.width())
        , int(rect.height())};
}

} // unnamed namespace

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
    // TODO set src rect
    m_texture.sourceRect = toSDL_Rect(srcRect());
    m_texture.sourceRect = SDL_Rect{0, 0, 100, 100};      // hard code
    // TODO set dst rect
    m_texture.destinationRect = toSDL_Rect(destRect());
    m_texture.destinationRect = SDL_Rect{0, 0, 100, 100}; // hard code
    assert(0 != subject());
    m_textureRederer = static_cast<Core::TextureRenderer*>(subject());
    assert(0 != m_textureRederer);
}

void GuiObject::onNotify()
{
    // TODO
    changeSourceRect(m_textureRederer->state());
}

void GuiObject::changeSourceRect(int state)
{
    int srcWidth = srcRect().width();
    Core::Rectangle rect = srcRect();
    rect.setX(srcWidth * state);
    m_texture.sourceRect = toSDL_Rect(rect);
}

GuiObject::GuiObject(const std::string& texture)
    : Core::GuiObject()
{
    setTextureLocation(texture);
}

} // namespace Sdl
