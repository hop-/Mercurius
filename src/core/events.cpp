#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"
#include "rectangle.hpp"

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
    , m_collisionDirection(Direction::None)
{
    assert(0 != m_objects.first);
    assert(0 != m_objects.second);
    assert(0 != m_objects.first->component<Collider>());
    assert(0 != m_objects.second->component<Collider>());
    m_isTrigger = (m_objects.first->component<Collider>()->isTrigger()
            || m_objects.second->component<Collider>()->isTrigger());
    Rectangle firstRect = m_objects.first->component<Collider>()->rect();
    Rectangle secondRect = m_objects.second->component<Collider>()->rect();
    if (firstRect.left() == secondRect.right()) {
        m_collisionDirection = Direction::Right;
    } else if (firstRect.right() == secondRect.left()) {
        m_collisionDirection = Direction::Left;
    } else if (firstRect.top() == secondRect.bottom()) {
        m_collisionDirection = Direction::Down;
    } else if (firstRect.bottom() == secondRect.top()) {
        m_collisionDirection = Direction::Up;
    }
}

Direction ObjectCollision::getCollisionSide(const LogicObject* object) const
{
    if (m_objects.first == object) {
        return directionForFirst();
    } else if (m_objects.second == object) {
        return directionForSecond();
    }
    return Direction::None;
}

const LogicObject*
ObjectCollision::another(const LogicObject* object) const
{
    if (!contains(object)) {
        return 0;
    }
    if (first() == object) {
        return second();
    } else {
        return first();
    }
}

bool ObjectCollision::less(Base::TypedBase* obj)
{
    return m_objects < static_cast<ObjectCollision*>(obj)->m_objects;
}

bool QuitEvent::less(Base::TypedBase*)
{
    return false;
}

OnSurface::OnSurface(const LogicObject* object)
    : m_object(object)
{}

bool OnSurface::less(Base::TypedBase* obj)
{
    return (this < obj);
}

OnAir::OnAir(const LogicObject* object)
    : m_object(object)
{}

bool OnAir::less(Base::TypedBase* obj)
{
    return (this < obj);
}


} // namespace Sdl
