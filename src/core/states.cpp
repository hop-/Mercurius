#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"
#include "vector.hpp"
#include "input_manager.hpp"

namespace Core
{

void Standing::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key || key->mode() == KeyEvent::Mode::Up) {
        return;
    }
    LogicObject* p = parent<LogicObject>();
    switch (key->key()) {
    case InputManager::Key::Right:
        p->changeState(new RunningRight);
        break;
    case InputManager::Key::Left:
        p->changeState(new RunningLeft);
    default:
        break;
    }
}

void Standing::init()
{
    // TODO change texture state
}

Command* Standing::command()
{
    assert(0 != parent<LogicObject>());
    return new Stand(parent<LogicObject>());
}

void Jumping::init()
{
    // TODO change texture state
}

void Jumping::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key) {
        return;
    }
    if (key->mode() == KeyEvent::Mode::Up
            && key->key() == InputManager::Key::Jump) {
        parent<LogicObject>()->removeState(this);
    }
}

Command* Jumping::command()
{
    if (0 == m_count) {
        return 0;
    }
    --m_count;
    return new Jump(parent<LogicObject>(), 100);
}

void RunningLeft::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key) {
        return;
    }
    LogicObject* p = parent<LogicObject>();
    if (key->mode() == KeyEvent::Mode::Down) {
        if (key->key() == InputManager::Key::Right) {
            p->changeState(new RunningRight);
        }
    } else {
        if (key->key() == InputManager::Key::Left) {
            p->changeState(new Standing);
        }
    }
}

void RunningLeft::init()
{
    // TODO change texture state
}

Command* RunningLeft::command()
{
    return new Accelerate(parent<LogicObject>()
            , Vector(1, 180));
}

void RunningRight::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key) {
        return;
    }
    LogicObject* p = parent<LogicObject>();
    if (key->mode() == KeyEvent::Mode::Down) {
        if (key->key() == InputManager::Key::Left) {
            p->changeState(new RunningLeft);
        }
    } else {
        if (key->key() == InputManager::Key::Right) {
            p->changeState(new Standing);
        }
    }
}

void RunningRight::init()
{
    // TODO change texture state
}

Command* RunningRight::command()
{
    return new Accelerate(parent<LogicObject>()
            , Vector(1, 0));
}

} // namespace Core
