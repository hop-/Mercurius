#include "event_manager.hpp"

#include <core/events.hpp>
#include <core/input_manager.hpp>

#include <base/event.hpp>

#include <SDL2/SDL.h>

namespace Sdl
{

namespace {

Core::KeyEvent::Modifier getModifier(SDL_Event event)
{
    Core::KeyEvent::Modifier m;
    switch(event.key.keysym.mod) {
        case KMOD_SHIFT:
            m = Core::KeyEvent::Modifier::Shift;
            break;
        case KMOD_CTRL:
            m = Core::KeyEvent::Modifier::Ctrl;
            break;
        case KMOD_ALT:
            m = Core::KeyEvent::Modifier::Alt;
            break;
        default:
            m = Core::KeyEvent::Modifier::None;
    }
    return m;
}

} // end of unnamed namespace

void InputHandler::
catchUserInput()
{
    SDL_Event event;
    Core::InputManager::Key k;
    if (SDL_PollEvent(&event)) {
        Base::Event* cevent = 0;
        switch (event.type) {
        case SDL_QUIT :
            cevent = new Core::QuitEvent;
            break;
        case SDL_KEYDOWN:
            if (event.key.repeat != 0) {
                break;
            }
            k = Core::InputManager::key(event.key.keysym.scancode);
            if (k == Core::InputManager::Key::None) {
                break;
            }
            cevent = new Core::KeyEvent(k
                        , Core::KeyEvent::Mode::Down, getModifier(event));
            break;
        case SDL_KEYUP:
            if (event.key.repeat != 0) {
                break;
            }
            k = Core::InputManager::key(event.key.keysym.scancode);
            if (k == Core::InputManager::Key::None) {
                break;
            }
            cevent = new Core::KeyEvent(k
                        , Core::KeyEvent::Mode::Up, getModifier(event));
            break;
        default:
            cevent = 0;
        }
        if (0 != cevent) {
            Base::EventManager::process(cevent);
        }
    }
}

void InputHandler::
delay(unsigned ms)
{
    SDL_Delay(ms);
}

unsigned InputHandler::
getTicks()
{
    return SDL_GetTicks();
}

} // namespace Sdl
