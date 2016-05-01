#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"

#include <assets/events.hpp>

namespace Core
{

Standing::Standing()
{
}

Standing::~Standing()
{
}

void Standing::onKeyEvent(Base::Event* e)
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

void Standing::onObjectCollision(Base::Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert (0 != c);
    LogicObject* p = parent<LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
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
}

OnLadder::~OnLadder()
{
}

void OnLadder::onKeyEvent(Base::Event* e)
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

void OnLadder::onObjectCollision(Base::Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert (0 != c);
    LogicObject* p = parent<LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
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
}

MoveOnLadder::~MoveOnLadder()
{
}

void MoveOnLadder::onKeyEvent(Base::Event* e)
{
    KeyEvent* k = KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == KeyEvent::Mode::Up && k->key() == m_stopKey) {
        parent<LogicObject>()->changeState(this, new OnLadder);
    }
}

void MoveOnLadder::onObjectCollision(Base::Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    assert (0 != c);
    LogicObject* p = parent<LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
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
    registerCallback<Assets::OnAir>(
            new Base::DelegateCreator<OnGround>(this, &OnGround::onAir));
}

OnGround::~OnGround()
{}

void OnGround::onKeyEvent(Base::Event* e)
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

void OnGround::onAir(Base::Event* e)
{
    Assets::OnAir* oa = Assets::OnAir::cast(e);
    assert(0 != oa);
    LogicObject* p = parent<LogicObject>();
    assert(0 != p);
    if (oa->object() != p) {
        return;
    }
    p->changeState(this, new Falling);
}

Jumping::Jumping()
{
    registerCallback<Assets::OnSurface>(
            new Base::DelegateCreator<Jumping>(this, &Jumping::onSurface));
}

Jumping::~Jumping()
{}

Jumping::Jumping(EngineUnit power)
    : Jumping()
{
    m_power = power;
}

void Jumping::onKeyEvent(Base::Event* e)
{
    KeyEvent* key = KeyEvent::cast(e);
    assert(0 != key);
    if (key->mode() == KeyEvent::Mode::Up
            && key->key() == InputManager::Key::Jump) {
        m_count = 0;
    }
}

void Jumping::onSurface(Base::Event* e)
{
    Assets::OnSurface* os = Assets::OnSurface::cast(e);
    assert(0 != os);
    LogicObject* p = parent<LogicObject>();
    assert(0 != p);
    if (os->object() != p) {
        return;
    }
    p->changeState(this, new OnGround());
}
// TODO activate Falling state if collide during Jumping

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
    registerCallback<Assets::OnSurface>(
            new Base::DelegateCreator<Falling>(this, &Falling::onSurface));
}

Falling::~Falling()
{}

Command* Falling::onInit()
{
    // TODO return command to change texture
    return 0;
}

void Falling::onSurface(Base::Event* e)
{
    Assets::OnSurface* os = Assets::OnSurface::cast(e);
    assert(0 != os);
    LogicObject* p = parent<LogicObject>();
    assert(0 != p);
    if (os->object() != p) {
        return;
    }
    p->changeState(this, new OnGround());
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
}

Running::~Running()
{
}

void Running::onKeyEvent(Base::Event* e)
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

void Running::onObjectCollision(Base::Event* e)
{
    ObjectCollision* c = ObjectCollision::cast(e);
    LogicObject* p = parent<LogicObject>();
    assert(c != 0);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
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

Command* LayerChanger::command()
{
    if (m_is_active) {
        return 0; // TODO return command which will change layer
    }
    return 0;
}

void LayerChanger::onKeyEvent(Base::Event*)
{
    // TODO handle ALT+Tab event
}

} // namespace Core
