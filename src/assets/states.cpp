#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"

#include <core/events.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>
#include <core/vector.hpp>

namespace Assets
{

void Standing::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    assert(0 != key);
    assert(0 != parent<Core::LogicObject>());
    if (key->mode() == Core::KeyEvent::Mode::Up) {
        return;
    }
    switch (key->key()) {
    case Core::InputManager::Key::Right:
        parent<Core::LogicObject>()->changeState(this
                , new Running(Core::HorizontalDirection::Right));
        break;
    case Core::InputManager::Key::Left:
        parent<Core::LogicObject>()->changeState(this
                , new Running(Core::HorizontalDirection::Left));
    default:
        break;
    }
}

void Standing::onObjectCollision(Base::Event* e)
{
    Core::ObjectCollision* c = Core::ObjectCollision::cast(e);
    assert (0 != c);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == Core::ObjectCollision::Status::Attached) {
            p->addState(new OnLadder);
        }
    }
}

Core::Command* Standing::onInit()
{
    // TODO return command to change texture
    return 0;
}

Core::Command* Standing::command()
{
    assert(0 != parent<Core::LogicObject>());
    return new Stand(parent<Core::LogicObject>());
}

void OnLadder::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* k = Core::KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == Core::KeyEvent::Mode::Up) {
        return;
    }
    assert(0 != parent<Core::LogicObject>());
    switch (k->key()) {
    case Core::InputManager::Key::Up:
        parent<Core::LogicObject>()->changeState(this, new MoveOnLadder(Core::VerticalDirection::Up));
        break;
    case Core::InputManager::Key::Down:
        parent<Core::LogicObject>()->changeState(this, new MoveOnLadder(Core::VerticalDirection::Down));
    default:
        break;
    }
}

void OnLadder::onObjectCollision(Base::Event* e)
{
    Core::ObjectCollision* c = Core::ObjectCollision::cast(e);
    assert (0 != c);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == Core::ObjectCollision::Status::Detached) {
            p->removeState(this);
        }
    }
}

Core::Command* OnLadder::onInit()
{
    return 0;
}

Core::Command* OnLadder::command()
{
    return new Stop(parent<Core::LogicObject>(), Core::Direction::Down);
}

MoveOnLadder::MoveOnLadder(Core::VerticalDirection d)
    : m_stopKey((d == Core::VerticalDirection::Up)
            ? Core::InputManager::Key::Up
            : Core::InputManager::Key::Down)
{}


void MoveOnLadder::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* k = Core::KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == Core::KeyEvent::Mode::Up && k->key() == m_stopKey) {
        parent<Core::LogicObject>()->changeState(this, new OnLadder);
    }
}

void MoveOnLadder::onObjectCollision(Base::Event* e)
{
    Core::ObjectCollision* c = Core::ObjectCollision::cast(e);
    assert (0 != c);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert (0 != p);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == Core::ObjectCollision::Status::Detached) {
            p->removeState(this);
        }
    }
}

Core::Command* MoveOnLadder::onInit()
{
    // TODO return command to change texture
    return 0;
}

Core::Command* MoveOnLadder::command()
{
    const Core::UserUnit vY = 0.7;
    Core::VerticalDirection vd;
    if (m_stopKey == Core::InputManager::Key::Up) {
        vd = Core::VerticalDirection::Up;
    } else {
        vd = Core::VerticalDirection::Down;
    }
    return new SetYVelocity(parent<Core::LogicObject>(), vY, vd);
}

Core::Command* OnGround::onInit()
{
    // TODO return command to change texture
    return 0;
}

OnGround::OnGround()
{
    registerCallback<OnAir>(
            new Base::DelegateCreator<OnGround>(this, &OnGround::onAir));
}

void OnGround::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    assert(0 != key);
    if (key->mode() == Core::KeyEvent::Mode::Up) {
        return;
    }
    if (key->key() == Core::InputManager::Key::Jump) {
        parent<Core::LogicObject>()->changeState(this, new Jumping);
    }
}

void OnGround::onAir(Base::Event* e)
{
    OnAir* oa = OnAir::cast(e);
    assert(0 != oa);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    if (oa->object() != p) {
        return;
    }
    p->changeState(this, new Falling);
}

Jumping::Jumping()
{
    registerCallback<OnSurface>(
            new Base::DelegateCreator<Jumping>(this, &Jumping::onSurface));
}

Jumping::Jumping(Core::EngineUnit power)
    : Jumping()
{
    m_power = power;
}

void Jumping::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    assert(0 != key);
    if (key->mode() == Core::KeyEvent::Mode::Up
            && key->key() == Core::InputManager::Key::Jump) {
        m_count = 0;
    }
}

void Jumping::onSurface(Base::Event* e)
{
    OnSurface* os = OnSurface::cast(e);
    assert(0 != os);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    if (os->object() != p) {
        return;
    }
    p->changeState(this, new OnGround());
}
// TODO activate Falling state if collide during Jumping

Core::Command* Jumping::onInit()
{
    // TODO return command to change texture
    return 0;
}

Core::Command* Jumping::command()
{
    if (0 == m_count) {
        return 0;
    }
    --m_count;
    return new Jump(parent<Core::LogicObject>(), m_power);
}

Falling::Falling()
{
    registerCallback<OnSurface>(
            new Base::DelegateCreator<Falling>(this, &Falling::onSurface));
}

Core::Command* Falling::onInit()
{
    // TODO return command to change texture
    return 0;
}

void Falling::onSurface(Base::Event* e)
{
    OnSurface* os = OnSurface::cast(e);
    assert(0 != os);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    if (os->object() != p) {
        return;
    }
    p->changeState(this, new OnGround());
}

Running::Running(Core::HorizontalDirection d)
    : m_direction(d)
    , m_antiDirection((d == Core::HorizontalDirection::Left)
            ? Core::HorizontalDirection::Right
            : Core::HorizontalDirection::Left)
    , m_changeDir((d == Core::HorizontalDirection::Left)
            ? Core::InputManager::Key::Right
            : Core::InputManager::Key::Left)
    , m_stopRunning((d == Core::HorizontalDirection::Left)
            ? Core::InputManager::Key::Left
            : Core::InputManager::Key::Right)
{}

void Running::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    assert(0 != key);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    if (key->mode() == Core::KeyEvent::Mode::Down) {
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
    Core::ObjectCollision* c = Core::ObjectCollision::cast(e);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(c != 0);
    if (!c->contains(p)) {
        return;
    }
    assert(0 != c->another(p));
    if (c->another(p)->typeName() == "ladder") { // TODO hardcoded
        if (c->status() == Core::ObjectCollision::Status::Attached) {
            p->addState(new OnLadder);
        }
    }
}

Core::Command* Running::onInit()
{
    // TODO return command to change texture and set direction
    assert(0 != parent<Core::LogicObject>());
    assert(0 != parent<Core::LogicObject>()
            ->component<Core::TextureRenderer>());
    parent<Core::LogicObject>()
        ->component<Core::TextureRenderer>()->setDirection(m_direction);
    return 0;
}

Core::Command* Running::command()
{
    float angle;
    if (m_direction == Core::HorizontalDirection::Left) {
        angle = 180;
    } else {
        angle = 0;
    }
    return new Accelerate(parent<Core::LogicObject>()
            , Core::Vector(1, angle));
}

Core::Command* LayerChanger::command()
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

} // namespace Assets