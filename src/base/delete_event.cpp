#include "delete_event.hpp"
#include "object.hpp"

namespace Base
{

DeleteEvent::
DeleteEvent(Object* o)
    : m_object(o)
{
    assert(0 != m_object);
}

DeleteEvent::
~DeleteEvent()
{
    assert(0 == m_object);
}

void DeleteEvent::
trigger()
{
    delete m_object;
    m_object = 0;
}

} // namespace Base
