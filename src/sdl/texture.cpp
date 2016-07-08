#include "texture.hpp"

#include <SDL2/SDL_image.h>
#include <iostream>

namespace Sdl
{

std::map<std::string, SDL_Texture*> Texture::m_textures;

void Texture::
initTexture(SDL_Renderer* r, std::string path)
{
    if (m_textures.find(path) != m_textures.end()) {
        texture = m_textures[path];
        return;
    }
    texture = m_textures[path] = IMG_LoadTexture(r, path.c_str());

}

} // namespace Sdl
