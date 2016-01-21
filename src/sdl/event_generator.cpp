#include "event_generator.hpp"

#include <core/events.hpp>

#include <SDL2/SDL.h>

namespace Sdl
{

void EventGenerator::catchEvent()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        Core::Event* cevent = 0;
        switch (event.type) {
        case SDL_QUIT :
            cevent = new Core::QuitEvent;
        break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (event.type == SDL_KEYDOWN) {
                cevent = new Core::KeyEvent(event.key.keysym.sym
                        , Core::KeyEvent::Mode::Down);
            } else {
                cevent = new Core::KeyEvent(event.key.keysym.sym
                        , Core::KeyEvent::Mode::Up);
            }
        break;
        default:
            cevent = 0;
        }
        if (0 != cevent) {
            setCatchedEvent(cevent);
        }
    }
}

unsigned EventGenerator::getTicks()
{
    return SDL_GetTicks();
}

} // namespace Sdl
