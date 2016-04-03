#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"

namespace Core
{

void Standing::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key || key->mode() == KeyEvent::Mode::Up) {
        return;
    }
    switch (key->key()) {
    case InputManager::Key::Right:
        parent<LogicObject>()->changeState(new Running(HorizontalDirection::Right));
        break;
    case InputManager::Key::Left:
        parent<LogicObject>()->changeState(new Running(HorizontalDirection::Left));
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

void OnGround::init()
{
    // TODO change texture state
}

void OnGround::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 == key || key->mode() == KeyEvent::Mode::Up) {
        return;
    }
    if (key->key() == InputManager::Key::Jump) {
        parent<LogicObject>()->changeState(new Jumping);
    }
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
    if (0 != key) {
        if (key->mode() == KeyEvent::Mode::Up
                && key->key() == InputManager::Key::Jump) {
            m_count = 0;
        }
        return;
    }
    ObjectCollision* c = ObjectCollision::cast(e);
    if (0 == c
            || c->isTrigger()
            || c->status() == ObjectCollision::Status::Detached) {
        return;
    }
    LogicObject* p = parent<LogicObject>();
    int isFirst = false;
    if (c->first() == p) {
        isFirst = true;
    } else if (c->second() != p){
        return;
    }
    Direction d;
    if (isFirst) {
        d = c->directionForFirst();
    } else {
        d = c->directionForSecond();
    }
    if (d == Direction::Up) {
        parent<LogicObject>()->changeState(new OnGround());
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

Running::Running(HorizontalDirection d)
    : m_direction(d)
    , m_antiDirection((d == HorizontalDirection::Left)
            ? HorizontalDirection::Right
            : HorizontalDirection::Left)
    , m_changeDir((d == HorizontalDirection::Left)
            ? InputManager::Key::Right
            : InputManager::Key::Left)
    , m_stopRunning((d == HorizontalDirection::Left)
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
    assert(0 != p);
    if (key->mode() == KeyEvent::Mode::Down) {
        if (key->key() == m_changeDir) {
            p->changeState(new Running(m_antiDirection));
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
    assert(0 != parent<LogicObject>());
    assert(0 != parent<LogicObject>()->component<TextureRenderer>());
    parent<LogicObject>()
        ->component<TextureRenderer>()->setDirection(m_direction);
}

Command* Running::command()
{
    float angle;
    if (m_direction == HorizontalDirection::Left) {
        angle = 180;
    } else {
        angle = 0;
    }
    return new Accelerate(parent<LogicObject>()
            , Vector(1, angle));
}

} // namespace Core
