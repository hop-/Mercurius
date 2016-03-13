#include "event_manager.hpp"

#include <core/events.hpp>
#include <core/game.hpp>
#include <core/input_manager.hpp>

#include <SDL2/SDL.h>

#include <iostream>

namespace Sdl
{

void EventManager::catchEvent()
{
    SDL_Event event;
    Core::InputManager im =
        Core::Game::getInstance()->getInputManager();
    Core::InputManager::Key k;
    if (SDL_PollEvent(&event)) {
        Core::Event* cevent = 0;
        switch (event.type) {
        case SDL_QUIT :
            cevent = new Core::QuitEvent;
            break;
        case SDL_KEYDOWN:
            if (event.key.repeat != 0) {
                break;
            }
            k = im[event.key.keysym.scancode];
            if (k == Core::InputManager::Key::None) {
                break;
            }
            cevent = new Core::KeyEvent(k
                        , Core::KeyEvent::Mode::Down);
            break;
        case SDL_KEYUP:
            if (event.key.repeat != 0) {
                break;
            }
            k = im[event.key.keysym.scancode];
            if (k == Core::InputManager::Key::None) {
                break;
            }
            cevent = new Core::KeyEvent(k
                        , Core::KeyEvent::Mode::Up);
            break;
        default:
            cevent = 0;
        }
        if (0 != cevent) {
            push(cevent);
        }
    }
}

unsigned EventManager::getTicks()
{
    return SDL_GetTicks();
}

} // namespace Sdl
