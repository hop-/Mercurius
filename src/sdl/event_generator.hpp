#ifndef _SDL_EVENT_GENERATOR_HPP_
#define _SDL_EVENT_GENERATOR_HPP_

#include "core/event_generator.hpp"

namespace Sdl
{

class EventGenerator
    : public Core::EventGenerator
{
public:
    void catchEvent();
    unsigned getTicks();
};

} // namespace Sdl

#endif //_SDL_EVENT_GENERATOR_HPP_
