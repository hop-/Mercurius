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
             Modifier modifier = Modifier::None);
    InputManager::Key key() const;
    Mode mode() const;
    Modifier modifier() const;
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
    MouseClickEvent(int x, int y, Button button, Mode mode);
    int x() const;
    int y() const;
    Button button() const;
    Mode mode() const;
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
    const LogicObject* first() const;
    const LogicObject* second() const;
    bool contains(const LogicObject* object) const;
    bool isTrigger() const;
    Status status() const;
    Direction directionForFirst() const;
    Direction directionForSecond() const;
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
    const LogicObject* object() const;

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
    const LogicObject* object() const;

private:
    OnAir(const OnAir&) = delete;
    OnAir& operator=(const OnAir&) = delete;
};


} // namespace Core

#endif //_CORE_EVENTS_HPP_
