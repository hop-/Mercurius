#include "gui_object.hpp"
#include "texture.hpp"

#include <core/gui.hpp>
#include <core/frame.hpp>

#include <SDL2/SDL_image.h>

SDL_Rect toSDL_Rect(const Core::Rectangle& rect)
{
    return SDL_Rect{int(rect.position().x())
        , int(rect.position().y())
        , int(rect.width())
        , int(rect.height())};
}

namespace Sdl
{


void GuiObject::init()
{
    assert(0 != parent());
    assert(0 != parent()->frame());
    SDL_Renderer* renderer = static_cast<SDL_Renderer*>(
            parent()->frame()->renderer());
    assert(0 != renderer);
    m_texture.texture = IMG_LoadTexture(renderer,
            textureLocation().c_str());
    // TODO set src rect
    m_texture.sourceRect = toSDL_Rect(srcRect());
    // TODO set dst rect
    m_texture.destinationRect = toSDL_Rect(destRect());
}

void GuiObject::onNotify()
{
    // TODO
}

} // namespace Sdl
