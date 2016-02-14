#ifndef _CORE_TEXTURE_HPP_
#define _CORE_TEXTURE_HPP_

#include <SDL2/SDL.h>

namespace Sdl
{

struct Texture
{
    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
};

} // namespace Core

#endif //_CORE_TEXTURE_HPP_
