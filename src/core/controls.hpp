#ifndef _CORE_CONTROLS_HPP_
#define _CORE_CONTROLS_HPP_

#include <base/event.hpp>

#include <map>

namespace Core
{

class Command;

class Controls
{
    std::map<Base::Event*, Command*, Base::Event::Less> m_controlMap;

public:
    void add(Base::Event* event, Command* command);
    void remove(Base::Event* event);
    Command* getCommand(Base::Event* event);

public:
    Controls()
        : m_controlMap()
    {}
};

} // namespace Core

#endif //_CORE_CONTROLS_HPP_
