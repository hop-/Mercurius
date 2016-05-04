#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"

#include <core/events.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>
#include <core/vector.hpp>

#include <base/event_manager.hpp>

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

Standing::Standing()
{
    registerCallback<OnLadderEvent>(
            new Base::DelegateCreator<Standing>(this
                , &Standing::onLadder));
}

void Standing::onLadder(Base::Event* e)
{
    OnLadderEvent* l = OnLadderEvent::cast(e);
    assert(0 != l);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    if (l->object() != p) {
        return;
    }
    p->addState(new NearLadder);
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

NearLadder::NearLadder()
{
    registerCallback<OutLadderEvent>(
            new Base::DelegateCreator<NearLadder>(this
                , &NearLadder::outLadder));
}

void NearLadder::outLadder(Base::Event* e)
{
    OutLadderEvent* ol = OutLadderEvent::cast(e);
    assert(0 != ol);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    if (ol->object() != p) {
        return;
    }
    p->removeState(this);
}

void NearLadder::onKeyEvent(Base::Event* e)
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

OnLadder::OnLadder()
{
    registerCallback<Core::KeyEvent>(
            new Base::DelegateCreator<OnLadder>(this
                , &OnLadder::onKeyEvent2));
}

Core::Command* OnLadder::onInit()
{
    return 0;
}

Core::Command* OnLadder::command()
{
    return new Stop(parent<Core::LogicObject>(), Core::Direction::Down);
}

void OnLadder::onKeyEvent2(Base::Event* e)
{
    Core::KeyEvent* k = Core::KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == Core::KeyEvent::Mode::Down
            && k->key() == Core::InputManager::Key::Jump) {
        Base::EventManager::process(new Core::OnAir(parent<Core::LogicObject>()));
        parent<Core::LogicObject>()->changeState(this, new NearLadder);
    }
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
    registerCallback<Core::OnAir>(
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
    Core::OnAir* oa = Core::OnAir::cast(e);
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
    registerCallback<Core::OnSurface>(
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
    Core::OnSurface* os = Core::OnSurface::cast(e);
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
    return new Jump(parent<Core::LogicObject>(), 20*m_power);
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
    registerCallback<Core::OnSurface>(
            new Base::DelegateCreator<Falling>(this, &Falling::onSurface));
}

Core::Command* Falling::onInit()
{
    // TODO return command to change texture
    return 0;
}

void Falling::onSurface(Base::Event* e)
{
    Core::OnSurface* os = Core::OnSurface::cast(e);
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
{
    registerCallback<OnLadderEvent>(
            new Base::DelegateCreator<Running>(this
                , &Running::onLadder));
}

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

void Running::onLadder(Base::Event* e)
{
    OnLadderEvent* l = OnLadderEvent::cast(e);
    assert(0 != l);
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    if (l->object() != p) {
        return;
    }
    p->addState(new NearLadder);
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
    Core::Direction d;
    if (m_direction == Core::HorizontalDirection::Left) {
        d = Core::Direction::Left;
    } else {
        d = Core::Direction::Right;
    }
    return new ApplyMovement(parent<Core::LogicObject>(), 500, d);
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
