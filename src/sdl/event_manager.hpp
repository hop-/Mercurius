#ifndef _SDL_EVENT_MANAGER_HPP_
#define _SDL_EVENT_MANAGER_HPP_

#include <core/event_manager.hpp>

namespace Sdl
{

class EventManager
    : public Core::EventManager
{
public:
    void catchEvent();
    unsigned getTicks();
};

} // namespace Sdl

#endif //_SDL_EVENT_MANAGER_HPP_
