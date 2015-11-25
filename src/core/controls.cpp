#include "controls.hpp"

namespace Core
{

void Controls::add(Event* event, Command* command)
{
    m_controlMap.insert(std::pair<Event*, Command*>(event, command));
}

void Controls::remove(Event* event)
{
    m_controlMap.erase(event);
}

Command* Controls::getCommand(Event* event)
{
    return m_controlMap[event];
}

} /// namespace Core
