#ifndef _CORE_TEXTURE_HPP_
#define _CORE_TEXTURE_HPP_

#include <SDL2/SDL.h>

#include <string>
#include <map>

namespace Sdl
{

struct Texture
{
    SDL_Texture* texture = 0;
    SDL_Rect sourceRect{0, 0, 0, 0};
    SDL_Rect destinationRect{0, 0, 0, 0};
    SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
    void initTexture(SDL_Renderer* r, std::string path);

private:
    static std::map<std::string, SDL_Texture*> m_textures;
};

} // namespace Core

#endif //_CORE_TEXTURE_HPP_
