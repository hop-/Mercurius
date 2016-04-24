#ifndef _SDL_EVENT_MANAGER_HPP_
#define _SDL_EVENT_MANAGER_HPP_

#include <core/event_manager.hpp>

namespace Sdl
{

class InputHandler
    : public Core::InputHandler
{
public:
    unsigned getTicks() override final;
    void catchUserInput() override final;
};

} // namespace Sdl

#endif //_SDL_EVENT_MANAGER_HPP_
