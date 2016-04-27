#include "event_manager.hpp"

#include "layer.hpp"

#include <base/event.hpp>

#include <cassert>

namespace Core
{

void EventManager::process(Base::Event* e)
{
    assert(0 != e);
    e->trigger();
    delete e;
}

} // namespace core
