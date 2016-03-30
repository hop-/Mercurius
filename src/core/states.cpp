#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"
#include "logic_object.hpp"

namespace Core
{

void Standing::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key || key->mode() == KeyEvent::Mode::Up) {
        return;
    }
    switch (key->key()) {
    case InputManager::Key::Jump:
        parent<LogicObject>()->addState(new Jumping);
        break;
    case InputManager::Key::Right:
        parent<LogicObject>()->changeState(new Running(Running::Direction::Right));
        break;
    case InputManager::Key::Left:
        parent<LogicObject>()->changeState(new Running(Running::Direction::Left));
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

Jumping::Jumping(EngineUnit power)
    : m_power(power)
{}

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
    return new Jump(parent<LogicObject>(), m_power);
}

Running::Running(Running::Direction d)
    : m_direction(d)
    , m_antiDirection((d == Direction::Left)
            ? Direction::Right
            : Direction::Left)
    , m_changeDir((d == Direction::Left)
            ? InputManager::Key::Right
            : InputManager::Key::Left)
    , m_stopRunning((d == Direction::Left)
            ? InputManager::Key::Left
            : InputManager::Key::Right)
{}

void Running::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key) {
        return;
    }
    LogicObject* p = parent<LogicObject>();
    if (key->mode() == KeyEvent::Mode::Down) {
        if (key->key() == m_changeDir) {
            p->changeState(new Running(m_antiDirection));
        }
        if (key->key() == InputManager::Key::Jump) {
            p->addState(new Jumping);
        }
    } else {
        if (key->key() == m_stopRunning) {
            p->changeState(new Standing);
        }
    }
}

void Running::init()
{
    // TODO change texture state
}

Command* Running::command()
{
    float angle;
    if (m_direction == Direction::Left) {
        angle = 180;
    } else {
        angle = 0;
    }
    return new Accelerate(parent<LogicObject>()
            , Vector(1, angle));
}

} // namespace Core
