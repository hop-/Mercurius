#ifndef _CORE_EVENTS_HPP_
#define _CORE_EVENTS_HPP_

#include "event.hpp"
#include <core/input_manager.hpp>

namespace Core
{

class LogicObject;

class KeyEvent
    : public EventCreator<KeyEvent>
{
public:
    enum class Mode {Up, Down};

private:
    InputManager::Key m_keyCode;
    Mode m_mode;

public:
    KeyEvent(InputManager::Key keyCode, Mode mode)
    : m_keyCode(keyCode)
    , m_mode(mode)
    {}

    inline InputManager::Key key() const
    {
        return m_keyCode;
    }

    inline Mode mode() const
    {
        return m_mode;
    }

private:
    bool less(Base::TypedBase* obj);
};

class MouseClickEvent
    : public EventCreator<MouseClickEvent>
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

private:
    bool less(Base::TypedBase* obj);
};

class ObjectCollision
    : public EventCreator<ObjectCollision>
{
public:
    using ObjectPair = std::pair<const LogicObject*, const LogicObject*>;
    enum class Status {Collided, NotCollided};

private:
    ObjectPair m_objects;
    Status m_status;

public:
    ObjectCollision(ObjectPair pair, Status status)
        : m_objects(pair)
        , m_status(status)
    {}

    inline const LogicObject* first() const
    {
        return m_objects.first;
    }

    inline const LogicObject* second() const
    {
        return m_objects.second;
    }

    inline Status status() const
    {
        return m_status;
    }

private:
    bool less(Base::TypedBase* obj);
};

class QuitEvent
    : public EventCreator<QuitEvent>
{
private:
    bool less(Base::TypedBase* obj);
};

} // namespace Core

#endif //_CORE_EVENTS_HPP_
