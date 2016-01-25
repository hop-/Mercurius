#include "gui_object.hpp"
#include "texture.hpp"

#include <core/gui.hpp>
#include <core/frame.hpp>

#include <SDL2/SDL_image.h>

namespace Sdl
{


void GuiObject::init()
{
    Core::Texture* texture = new Core::Texture;
    SDL_Renderer* renderer = static_cast<SDL_Renderer*>(
            parent()->frame()->renderer());
    assert(0 != renderer);
    texture->texture = IMG_LoadTexture(renderer,
            textureLocation().c_str());
    // TODO set src rect
    // TODO set dst rect
    setTexture(texture);
}

void GuiObject::onNotify()
{}

} // namespace Sdl
