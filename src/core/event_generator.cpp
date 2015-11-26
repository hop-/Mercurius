#include "event_generator.hpp"

#include "event.hpp"
#include "layer.hpp"

#include <cassert>

namespace Core
{

EventGenerator::EventGenerator()
    : m_catchedEvent(0)
{}

Event* EventGenerator::getEvent()
{
    return m_catchedEvent;
}

Command* EventGenerator::getCommand(Layer* layer)
{
    assert(0 != layer);
    return layer->getCommand(m_catchedEvent);
}

} // namespace core
