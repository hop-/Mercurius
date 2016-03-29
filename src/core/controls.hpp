#ifndef _CORE_CONTROLS_HPP_
#define _CORE_CONTROLS_HPP_

#include "event.hpp"

#include <map>

namespace Core
{

class Command;

class Controls
{
    std::map<Event*, Command*, Event::Less> m_controlMap;

public:
    void add(Event* event, Command* command);
    void remove(Event* event);
    Command* getCommand(Event* event);

public:
    Controls()
        : m_controlMap()
    {}
};

} // namespace Core

#endif //_CORE_CONTROLS_HPP_
