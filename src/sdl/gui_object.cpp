#include "gui_object.hpp"
#include "texture.hpp"

#include <SDL2/SDL_image.h>

namespace Sdl
{


void GuiObject::init(SDL_Renderer* renderer)
{
    Core::Texture* texture = new Core::Texture;
    texture->texture = IMG_LoadTexture(renderer,
            textureLocation().c_str());
    // TODO set src rect
    // TODO set dst rect
    setTexture(texture);
}


} // namespace Sdl
