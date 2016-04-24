#include "event_manager.hpp"

#include "event.hpp"
#include "layer.hpp"

#include <cassert>

namespace Core
{

void EventManager::process(Event* e)
{
    assert(0 != e);
    e->trigger();
    delete e;
}

} // namespace core
