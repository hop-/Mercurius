#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"
#include "rectangle.hpp"

namespace Core
{

KeyEvent::
KeyEvent(InputManager::Key keyCode,
        Mode mode,
        Modifier modifier)
    : m_keyCode(keyCode)
    , m_mode(mode)
    , m_modifier(modifier)
{}

InputManager::Key KeyEvent::
key() const
{
    return m_keyCode;
}

KeyEvent::Mode KeyEvent::
mode() const
{
    return m_mode;
}

KeyEvent::Modifier KeyEvent::
modifier() const
{
    return m_modifier;
}

MouseClickEvent::
MouseClickEvent(int x, int y, Button b, Mode m)
    : m_x(x)
    , m_y(y)
    , m_button(b)
    , m_mode(m)
{}

int MouseClickEvent::
x() const
{
    return m_x;
}

int MouseClickEvent::
y() const
{
    return m_y;
}

MouseClickEvent::Button MouseClickEvent::
button() const
{
    return m_button;
}

MouseClickEvent::Mode MouseClickEvent::
mode() const
{
    return m_mode;
}

ObjectCollision::
ObjectCollision(ObjectPair pair, Status status)
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

Direction ObjectCollision::
getCollisionSide(const LogicObject* object) const
{
    if (m_objects.first == object) {
        return directionForFirst();
    } else if (m_objects.second == object) {
        return directionForSecond();
    }
    return Direction::None;
}

const LogicObject* ObjectCollision::
another(const LogicObject* object) const
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

const LogicObject* ObjectCollision::
first() const
{
    return m_objects.first;
}

const LogicObject* ObjectCollision::
second() const
{
    return m_objects.second;
}

bool ObjectCollision::
contains(const LogicObject* object) const
{
    return (m_objects.first == object || m_objects.second == object);
}

bool ObjectCollision::
isTrigger() const
{
    return m_isTrigger;
}

ObjectCollision::Status ObjectCollision::
status() const
{
    return m_status;
}

Direction ObjectCollision::
directionForFirst() const
{
    return m_collisionDirection;
}

Direction ObjectCollision::
directionForSecond() const
{
    switch (m_collisionDirection) {
        case Direction::Left:
            return Direction::Right;
        case Direction::Right:
            return Direction::Left;
        case Direction::Up:
            return Direction::Down;
        case Direction::Down:
            return Direction::Up;
        case Direction::None:
            return Direction::None;
    }
    return Direction::None;
}

OnSurface::
OnSurface(const LogicObject* object)
    : m_object(object)
{}

const LogicObject* OnSurface::
object() const
{
    return m_object;
}

OnAir::
OnAir(const LogicObject* object)
    : m_object(object)
{}

const LogicObject* OnAir::
object() const
{
    return m_object;
}

} // namespace Sdl
