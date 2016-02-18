#ifndef _SDL_MERCURIUS_HPP_
#define _SDL_MERCURIUS_HPP_

#include <core/game.hpp>

namespace Sdl
{

class Mercurius
{
public:
    static void start();

private:
    static void loadLayers(Core::Game&);
};

} // namespace Sdl

#endif // _SDL_MERCURIUS_HPP_
