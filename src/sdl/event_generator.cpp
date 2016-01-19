#include "event_generator.hpp"

#include <SDL2/SDL.h>

namespace Sdl
{


void EventGenerator::catchEvent()
{
    // TODO
}

unsigned EventGenerator::getTicks()
{
    return SDL_GetTicks();
}


} // namespace Sdl
