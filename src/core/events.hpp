#ifndef _CORE_EVENTS_HPP_
#define _CORE_EVENTS_HPP_

#include "input_manager.hpp"
#include "units.hpp"

#include <base/event.hpp>

namespace Core
{

class LogicObject;

class KeyEvent
    : public Base::EventCreator<KeyEvent>
{
public:
    enum class Mode {Up, Down};
    enum class Modifier {None, Ctrl, Alt, Shift};

private:
    InputManager::Key m_keyCode;
    Mode m_mode;
    Modifier m_modifier;

public:
    KeyEvent(InputManager::Key keyCode,
             Mode mode,
             Modifier modifier = Modifier::None)
    : m_keyCode(keyCode)
    , m_mode(mode)
    , m_modifier(modifier)
    {}

    inline InputManager::Key key() const
    {
        return m_keyCode;
    }

    inline Mode mode() const
    {
        return m_mode;
    }

    inline Modifier modifier() const
    {
        return m_modifier;
    }
};

class MouseClickEvent
    : public Base::EventCreator<MouseClickEvent>
{
public:
    enum class Mode {Up, Down};
    enum class Button {Right, Left, Middle};

private:
    int m_x;
    int m_y;
    Button m_button;
    Mode m_mode;

public:
    MouseClickEvent(int x, int y, Button button, Mode mode)
        : m_x(x)
        , m_y(y)
        , m_button(button)
        , m_mode(mode)
    {}

    inline int x() const
    {
        return m_x;
    }

    inline int y() const
    {
        return m_y;
    }

    inline Button button() const
    {
        return m_button;
    }

    inline Mode mode() const
    {
        return m_mode;
    }
};

class ObjectCollision
    : public Base::EventCreator<ObjectCollision>
{
public:
    using ObjectPair = std::pair<const LogicObject*, const LogicObject*>;
    enum class Status {Attached, Detached};

private:
    ObjectPair m_objects;
    Status m_status;
    bool m_isTrigger = true;
    Direction m_collisionDirection;

public:
    ObjectCollision(ObjectPair pair, Status status);
    Direction getCollisionSide(const LogicObject* object) const;
    const LogicObject* another(const LogicObject* object) const;

    inline const LogicObject* first() const
    {
        return m_objects.first;
    }

    inline const LogicObject* second() const
    {
        return m_objects.second;
    }

    inline bool contains(const LogicObject* object) const
    {
        return (m_objects.first == object || m_objects.second == object);
    }

    inline bool isTrigger() const
    {
        return m_isTrigger;
    }

    inline Status status() const
    {
        return m_status;
    }

    inline Direction directionForFirst() const
    {
        return m_collisionDirection;
    }

    inline Direction directionForSecond() const
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
};

class QuitEvent
    : public Base::EventCreator<QuitEvent>
{};

class OnSurface
    : public Base::EventCreator<OnSurface>
{
    const LogicObject* m_object;

public:
    OnSurface(const LogicObject* object);

    inline const LogicObject* object() const
    {
        return m_object;
    }

private:
    OnSurface(const OnSurface&) = delete;
    OnSurface& operator=(const OnSurface&) = delete;
};

class OnAir
    : public Base::EventCreator<OnAir>
{
    const LogicObject* m_object;

public:
    OnAir(const LogicObject* object);

    inline const LogicObject* object() const
    {
        return m_object;
    }

private:
    OnAir(const OnAir&) = delete;
    OnAir& operator=(const OnAir&) = delete;
};


} // namespace Core

#endif //_CORE_EVENTS_HPP_
