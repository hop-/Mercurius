#include "event_manager.hpp"
#include "event.hpp"

#include <cassert>

namespace Base
{

EventManager::Events EventManager::m_deleteEvents;

void EventManager::process(Base::Event* e)
{
    assert(0 != e);
    e->trigger();
    delete e;
}

void EventManager::processDeleteEvent(Base::Event* e)
{
    assert(0 != e);
    m_deleteEvents.push_back(e);
}

void EventManager::processAllDeleteEvents()
{
    for(auto e: m_deleteEvents) {
        process(e);
    }
    m_deleteEvents.clear();
    assert(m_deleteEvents.empty());
}

} // namespace Base
