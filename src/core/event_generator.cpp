#include "event_generator.hpp"

#include "event.hpp"
#include "layer.hpp"

namespace Core
{

Event* EventGenerator::getEvent()
{
    return m_catchedEvent;
}

Command* EventGenerator::getCommand(Layer* layer)
{
    return layer->getCommand(m_catchedEvent);
}

} // namespace core
