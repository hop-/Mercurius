#include "command.hpp"

namespace Core
{

Command::
Command(LogicObject* o)
    : m_object(o)
{
    assert(0 != m_object);
}

LogicObject* Command::
object()
{
    return m_object;
}

} // namespace Core
