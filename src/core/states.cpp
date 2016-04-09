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

Command* Standing::onInit()
{
    // TODO return command to change texture
    return 0;
}

Command* Standing::command()
{
    assert(0 != parent<LogicObject>());
    return new Stand(parent<LogicObject>());
}

Command* OnGround::onInit()
{
    // TODO return command to change texture
    return 0;
}

void OnGround::process(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    if (0 != key && key->mode() == KeyEvent::Mode::Down) {
        if (key->key() == InputManager::Key::Jump) {
            parent<LogicObject>()->changeState(new Jumping);
        }
        return;
    }
    ObjectCollision* c = ObjectCollision::cast(e);
    if (0 != c && !c->isTrigger() && c->contains(parent<LogicObject>())) {
        if (c->getCollisionSide(parent<LogicObject>()) == Direction::Up
                && c->status() == ObjectCollision::Status::Attached) {
            ++m_countOfGroundObjects;
        } else if (c->getCollisionSide(parent<LogicObject>())
                == Direction::None
                && c->status() == ObjectCollision::Status::Detached) {
            --m_countOfGroundObjects;
            if (m_countOfGroundObjects == 0) {
                parent<LogicObject>()->changeState(new Falling);
            }
        }
        return;
    }
}

Jumping::Jumping(EngineUnit power)
    : m_power(power)
{}

Command* Jumping::onInit()
{
    // TODO return command to change texture
    return 0;
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
            || !c->contains(parent<LogicObject>())
            || c->isTrigger()
            || c->status() == ObjectCollision::Status::Detached) {
        return;
    }
    if (c->getCollisionSide(parent<LogicObject>()) == Direction::Up) {
        parent<LogicObject>()->changeState(new OnGround());
    }
    // TODO activate Falling state if collide on air
}

Command* Jumping::command()
{
    if (0 == m_count) {
        return 0;
    }
    --m_count;
    return new Jump(parent<LogicObject>(), m_power);
}

Command* Falling::onInit()
{
    // TODO return command to change texture
    return 0;
}

void Falling::process(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    if (0 == c
            || !c->contains(parent<LogicObject>())
            || c->isTrigger()
            || c->status() == ObjectCollision::Status::Detached) {
        return;
    }
    if (c->getCollisionSide(parent<LogicObject>()) == Direction::Up) {
        parent<LogicObject>()->changeState(new OnGround());
    }
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

Command* Running::onInit()
{
    // TODO return command to change texture and set direction
    assert(0 != parent<LogicObject>());
    assert(0 != parent<LogicObject>()->component<TextureRenderer>());
    parent<LogicObject>()
        ->component<TextureRenderer>()->setDirection(m_direction);
    return 0;
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
