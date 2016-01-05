#include "event.hpp"

namespace Core
{

int Event::ID::m_count = 0;

Event::ID::ID()
    : m_id(++m_count)
{}

Event::ID::operator int() const
{
    return m_id; 
}

bool Event::Less::operator()(Event* lEvent, Event* rEvent) const
{
    assert(0 != lEvent);
    assert(0 != rEvent);
    if (lEvent->getType() == rEvent->getType()) {
        return lEvent->less(rEvent);
    }
    return lEvent->getType() < rEvent->getType();
}

} // namespace Core
