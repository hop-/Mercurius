#include "controls.hpp"

namespace Core
{

void Controls::add(Event* event, Command* command)
{
    assert(0 != event);
    assert(0 != command);
    m_controlMap.insert(std::pair<Event*, Command*>(event, command));
}

void Controls::remove(Event* event)
{
    assert(0 != event);
    m_controlMap.erase(event);
}

Command* Controls::getCommand(Event* event)
{
    assert(0 != event);
    try {
        return m_controlMap.at(event);
    } catch (const std::out_of_range& e) {
        return 0;
    }
}

} // namespace Core
