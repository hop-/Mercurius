#include "object.hpp"
#include "delete_event.hpp"
#include "event_manager.hpp"

#include <sstream>

namespace Base
{

static const std::string base_name = "baseObject";
static unsigned id = 0;

Object::Object()
    : m_name()
    , m_parent(0)
{
    std::stringstream converter;
    converter<<id++;
    std::string i;
    converter>>i;
    m_name = base_name + i;
}

Object::
~Object()
{
}

void Object::setName(const std::string& name)
{
    m_name = name;
}

const std::string& Object::name() const
{
    return m_name;
}

Object* Object::parent() const
{
    return m_parent;
}

void Object::setParent(Object* o)
{
    m_parent = o;
}

void Object::deleteLater()
{
    EventManager::processDeleteEvent(new DeleteEvent(this));
}

} // namespace Base
