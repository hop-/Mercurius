#include "event_manager.hpp"

#include "event.hpp"
#include "layer.hpp"

namespace Core
{

EventManager::EventManager()
{}

Event* EventManager::getEvent()
{
    return (m_eventQueue.empty())
        ? 0
        : m_eventQueue.front();
}

Command* EventManager::getCommand(Layer* layer)
{
    assert(0 != layer);
    return (m_eventQueue.empty())
        ? 0
        : layer->getCommand(m_eventQueue.front());
}

void EventManager::pop()
{
    if (m_eventQueue.size() > 0) {
        Event* e = m_eventQueue.front();
        m_eventQueue.pop();
        delete e;
    }
}

} // namespace core
