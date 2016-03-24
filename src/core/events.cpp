#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"

namespace Core
{


bool KeyEvent::less(Base::TypedBase* obj)
{
    KeyEvent* keyEvent = static_cast<KeyEvent*>(obj);
    return (m_keyCode < keyEvent->key()
            || (m_keyCode == keyEvent->key() && m_mode < keyEvent->mode()));
}

bool MouseClickEvent::less(Base::TypedBase* obj)
{
    MouseClickEvent* mouseEvent = static_cast<MouseClickEvent*>(obj);
    return (m_button < mouseEvent->button()
            && m_mode < mouseEvent->mode()
            && (m_y < mouseEvent->y()
                || (m_y == mouseEvent->y() && m_x < mouseEvent->x())));
}

ObjectCollision::ObjectCollision(ObjectPair pair, Status status)
    : m_objects(pair)
    , m_status(status)
{
    assert(0 != m_objects.first);
    assert(0 != m_objects.second);
    assert(0 != m_objects.first->component<Collider>());
    assert(0 != m_objects.second->component<Collider>());
    m_isTrigger = (m_objects.first->component<Collider>()->isTrigger()
            || m_objects.second->component<Collider>()->isTrigger());
}

bool ObjectCollision::less(Base::TypedBase* obj)
{
    return m_objects < static_cast<ObjectCollision*>(obj)->m_objects;
}

bool QuitEvent::less(Base::TypedBase* obj)
{
    return false;
}


} // namespace Sdl
