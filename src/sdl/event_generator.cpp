#include "event_generator.hpp"

#include <core/events.hpp>

#include <SDL2/SDL.h>

namespace Sdl
{


void EventGenerator::catchEvent()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT :
            setCatchedEvent(new Core::QuitEvent);
        break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (event.type == SDL_KEYDOWN) {
                setCatchedEvent(new Core::KeyEvent(event.key.keysym.sym
                        , Core::KeyEvent::Mode::Down));
            } else {
                setCatchedEvent(new Core::KeyEvent(event.key.keysym.sym
                        , Core::KeyEvent::Mode::Up));
            }
        break;
        }
    }
}

unsigned EventGenerator::getTicks()
{
    return SDL_GetTicks();
}


} // namespace Sdl
