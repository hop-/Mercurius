#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"

namespace Core
{

Standing::Standing()
{
    KeyEvent::registerCallback(&Standing::onKeyEvent, this);
    ObjectCollision::registerCallback(&Standing::onObjectCollision, this);
}

Standing::~Standing()
{
    KeyEvent::removeCallbacks(this);
    ObjectCollision::removeCallbacks(this);
}

void Standing::onKeyEvent(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    assert(0 != key);
    assert(0 != parent<LogicObject>());
    if (key->mode() == KeyEvent::Mode::Up) {
        return;
    }
    switch (key->key()) {
    case InputManager::Key::Right:
        parent<LogicObject>()->changeState(this, new Running(HorizontalDirection::Right));
        break;
    case InputManager::Key::Left:
        parent<LogicObject>()->changeState(this, new Running(HorizontalDirection::Left));
    default:
        break;
    }
}

void Standing::onObjectCollision(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert (0 != c);
    LogicObject* p = parent<LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->anouther(p));
    if (c->anouther(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == ObjectCollision::Status::Attached) {
            p->addState(new OnLadder);
        }
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

OnLadder::OnLadder()
{
    KeyEvent::registerCallback(&OnLadder::onKeyEvent, this);
    ObjectCollision::registerCallback(&OnLadder::onObjectCollision, this);
}

OnLadder::~OnLadder()
{
    KeyEvent::removeCallbacks(this);
    ObjectCollision::removeCallbacks(this);
}

void OnLadder::onKeyEvent(Event* e)
{
    KeyEvent* k = KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == KeyEvent::Mode::Up) {
        return;
    }
    assert(0 != parent<LogicObject>());
    switch (k->key()) {
    case InputManager::Key::Up:
        parent<LogicObject>()->changeState(this, new MoveOnLadder(VerticalDirection::Up));
        break;
    case InputManager::Key::Down:
        parent<LogicObject>()->changeState(this, new MoveOnLadder(VerticalDirection::Down));
    default:
        break;
    }
}

void OnLadder::onObjectCollision(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert (0 != c);
    LogicObject* p = parent<LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->anouther(p));
    if (c->anouther(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == ObjectCollision::Status::Detached) {
            p->removeState(this);
        }
    }
}

Command* OnLadder::onInit()
{
    return 0;
}

Command* OnLadder::command()
{
    return new Stop(parent<LogicObject>(), Direction::Down);
}

MoveOnLadder::MoveOnLadder(VerticalDirection d)
    : m_stopKey((d == VerticalDirection::Up)
            ? InputManager::Key::Up
            : InputManager::Key::Down)
{
    KeyEvent::registerCallback(&MoveOnLadder::onKeyEvent, this);
    ObjectCollision::registerCallback(
            &MoveOnLadder::onObjectCollision, this);
}

MoveOnLadder::~MoveOnLadder()
{
    KeyEvent::removeCallbacks(this);
    ObjectCollision::removeCallbacks(this);
}

void MoveOnLadder::onKeyEvent(Event* e)
{
    KeyEvent* k = KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == KeyEvent::Mode::Up && k->key() == m_stopKey) {
        parent<LogicObject>()->changeState(this, new OnLadder);
    }
}

void MoveOnLadder::onObjectCollision(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert (0 != c);
    LogicObject* p = parent<LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->anouther(p));
    if (c->anouther(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == ObjectCollision::Status::Detached) {
            p->removeState(this);
        }
    }
}

Command* MoveOnLadder::onInit()
{
    // TODO return command to change texture
    return 0;
}

Command* MoveOnLadder::command()
{
    const UserUnit vY = 0.7;
    VerticalDirection vd;
    if (m_stopKey == InputManager::Key::Up) {
        vd = VerticalDirection::Up;
    } else {
        vd = VerticalDirection::Down;
    }
    return new SetYVelocity(parent<LogicObject>(), vY, vd);
}

Command* OnGround::onInit()
{
    // TODO return command to change texture
    return 0;
}

OnGround::OnGround()
{
    KeyEvent::registerCallback(&OnGround::onKeyEvent, this);
    ObjectCollision::registerCallback(&OnGround::onObjectCollision, this);
}

OnGround::~OnGround()
{
    KeyEvent::removeCallbacks(this);
    ObjectCollision::removeCallbacks(this);
}

void OnGround::onKeyEvent(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    assert(0 != key);
    if (key->mode() == KeyEvent::Mode::Up) {
        return;
    }
    if (key->key() == InputManager::Key::Jump) {
        parent<LogicObject>()->changeState(this, new Jumping);
    }
}

void OnGround::onObjectCollision(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert(0 != c);
    if (c->isTrigger() || !c->contains(parent<LogicObject>())) {
        return;
    }
    if (c->getCollisionSide(parent<LogicObject>()) == Direction::Up
            && c->status() == ObjectCollision::Status::Attached) {
        ++m_countOfGroundObjects;
    } else if (c->getCollisionSide(parent<LogicObject>())
            == Direction::None
            && c->status() == ObjectCollision::Status::Detached) {
        --m_countOfGroundObjects;
        if (m_countOfGroundObjects == 0) {
            parent<LogicObject>()->changeState(this, new Falling);
        }
    }
}

Jumping::Jumping()
{
    KeyEvent::registerCallback(&Jumping::onKeyEvent, this);
    ObjectCollision::registerCallback(&Jumping::onObjectCollision, this);
}

Jumping::~Jumping()
{
    KeyEvent::removeCallbacks(this);
    ObjectCollision::removeCallbacks(this);
}

Jumping::Jumping(EngineUnit power)
    : Jumping()
{
    m_power = power;
}

void Jumping::onKeyEvent(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    assert(0 != key);
    if (key->mode() == KeyEvent::Mode::Up
            && key->key() == InputManager::Key::Jump) {
        m_count = 0;
    }
}

void Jumping::onObjectCollision(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert(0 != c);
    if (!c->contains(parent<LogicObject>())
            || c->isTrigger()
            || c->status() == ObjectCollision::Status::Detached) {
        return;
    }
    if (c->getCollisionSide(parent<LogicObject>()) == Direction::Up) {
        parent<LogicObject>()->changeState(this, new OnGround());
    }
    // TODO activate Falling state if collide on air
}

Command* Jumping::onInit()
{
    // TODO return command to change texture
    return 0;
}

Command* Jumping::command()
{
    if (0 == m_count) {
        return 0;
    }
    --m_count;
    return new Jump(parent<LogicObject>(), m_power);
}

Falling::Falling()
{
    ObjectCollision::registerCallback(&Falling::onObjectCollision, this);
}

Falling::~Falling()
{
    ObjectCollision::removeCallbacks(this);
}

Command* Falling::onInit()
{
    // TODO return command to change texture
    return 0;
}

void Falling::onObjectCollision(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert(0 != c);
    if (!c->contains(parent<LogicObject>())
            || c->isTrigger()
            || c->status() == ObjectCollision::Status::Detached) {
        return;
    }
    if (c->getCollisionSide(parent<LogicObject>()) == Direction::Up) {
        parent<LogicObject>()->changeState(this, new OnGround());
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
{
    KeyEvent::registerCallback(&Running::onKeyEvent, this);
    ObjectCollision::registerCallback(&Running::onObjectCollision, this);
}

Running::~Running()
{
    KeyEvent::removeCallbacks(this);
    ObjectCollision::removeCallbacks(this);
}

void Running::onKeyEvent(Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    assert(0 != key);
    LogicObject* p = parent<LogicObject>();
    assert(0 != p);
    if (key->mode() == KeyEvent::Mode::Down) {
        if (key->key() == m_changeDir) {
            p->changeState(this, new Running(m_antiDirection));
        }
    } else {
        if (key->key() == m_stopRunning) {
            p->changeState(this, new Standing);
        }
    }
}

void Running::onObjectCollision(Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    LogicObject* p = parent<LogicObject>();
    assert(c != 0);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->anouther(p));
    if (c->anouther(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == ObjectCollision::Status::Attached) {
            p->addState(new OnLadder);
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
