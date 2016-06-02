#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"

#include <core/events.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>
#include <core/vector.hpp>

#include <base/event_manager.hpp>

#define OWNER parent<Core::LogicObject>

namespace Assets
{

void Standing::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    assert(0 != key);
    assert(0 != OWNER());
    if (key->mode() == Core::KeyEvent::Mode::Up) {
        return;
    }
    switch (key->key()) {
    case Core::InputManager::Key::Right:
        OWNER()->changeState(this
                , new Running(Core::HorizontalDirection::Right));
        break;
    case Core::InputManager::Key::Left:
        OWNER()->changeState(this
                , new Running(Core::HorizontalDirection::Left));
    default:
        break;
    }
}

Standing::Standing()
{
    registerCallback<LadderEnter>(
            new Base::DelegateCreator<Standing>(this
                , &Standing::onLadder));
}

void Standing::onLadder(Base::Event* e)
{
    LadderEnter* l = LadderEnter::cast(e);
    assert(0 != l);
    Core::LogicObject* p = OWNER();
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
    assert(0 != OWNER());
    return new Stand(OWNER());
}

NearLadder::NearLadder()
{
    registerCallback<LadderExit>(
            new Base::DelegateCreator<NearLadder>(this
                , &NearLadder::outLadder));
}

void NearLadder::outLadder(Base::Event* e)
{
    LadderExit* ol = LadderExit::cast(e);
    assert(0 != ol);
    Core::LogicObject* p = OWNER();
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
    assert(0 != OWNER());
    switch (k->key()) {
    case Core::InputManager::Key::Up:
        Base::EventManager::process(new OnLadderEvent(OWNER()
                    , Core::VerticalDirection::Up));
        //OWNER()->removeState(this);
        break;
    case Core::InputManager::Key::Down:
        Base::EventManager::process(new OnLadderEvent(OWNER()
                    , Core::VerticalDirection::Down));
        //OWNER()->removeState(this);
    default:
        break;
    }
}

OnLadder::OnLadder()
{
    registerCallback<Core::KeyEvent>(
            new Base::DelegateCreator<OnLadder>(this
                , &OnLadder::onKeyEvent2));
    registerCallback<LadderExit>(
            new Base::DelegateCreator<OnLadder>(this
                , &OnLadder::outLadder));
}

Core::Command* OnLadder::onInit()
{
    return 0;
}

Core::Command* OnLadder::command()
{
    return new Stop(OWNER(), Core::Direction::Down);
}

void OnLadder::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* k = Core::KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == Core::KeyEvent::Mode::Up) {
        return;
    }
    assert(0 != OWNER());
    switch (k->key()) {
    case Core::InputManager::Key::Up:
        OWNER()->changeState(this, new MoveOnLadder(
                    Core::VerticalDirection::Up));
        break;
    case Core::InputManager::Key::Down:
        OWNER()->changeState(this, new MoveOnLadder(
                    Core::VerticalDirection::Down));
    default:
        break;
    }
}

void OnLadder::outLadder(Base::Event* e)
{
    LadderExit* ol = LadderExit::cast(e);
    assert(0 != ol);
    Core::LogicObject* p = OWNER();
    assert(0 != p);
    if (ol->object() != p) {
        return;
    }
    p->changeState(this, new Falling);
}

void OnLadder::onKeyEvent2(Base::Event* e)
{
    Core::KeyEvent* k = Core::KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == Core::KeyEvent::Mode::Down
            && k->key() == Core::InputManager::Key::Jump) {
        Base::EventManager::process(new Core::OnAir(OWNER()));
        OWNER()->changeState(this, new Jumping);
    }
}

MoveOnLadder::MoveOnLadder(Core::VerticalDirection d)
    : m_stopKey((d == Core::VerticalDirection::Up)
            ? Core::InputManager::Key::Up
            : Core::InputManager::Key::Down)
{
    registerCallback<Core::OnSurface>(
            new Base::DelegateCreator<MoveOnLadder>(this
                , &MoveOnLadder::onSurface));
}

void MoveOnLadder::onSurface(Base::Event* e)
{
    Core::OnSurface* os = Core::OnSurface::cast(e);
    assert(0 != os);
    Core::LogicObject* p = OWNER();
    assert(0 != p);
    if (os->object() != p) {
        return;
    }
    p->changeState(this, new OnGround());
}

void MoveOnLadder::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* k = Core::KeyEvent::cast(e);
    assert(0 != k);
    if (k->mode() == Core::KeyEvent::Mode::Up && k->key() == m_stopKey) {
        OWNER()->changeState(this, new OnLadder);
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
    return new SetYVelocity(OWNER(), vY, vd);
}

VerticalMovementState::VerticalMovementState()
{
    registerOnLadder();
}

void VerticalMovementState::registerOnLadder()
{
    registerCallback<OnLadderEvent>(
            new Base::DelegateCreator<VerticalMovementState>(this
                , &VerticalMovementState::onLadder));
}

void VerticalMovementState::onLadder(Base::Event* e)
{
    OnLadderEvent* ol = OnLadderEvent::cast(e);
    assert(0 != ol);
    if (ol->object() != OWNER()) {
        return;
    }
    if (ol->direction() == Core::VerticalDirection::None) {
        OWNER()->changeState(this, new OnLadder);
    } else {
        OWNER()->changeState(this, new MoveOnLadder(ol->direction()));
    }
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
        OWNER()->changeState(this, new Jumping);
    }
}

void OnGround::onAir(Base::Event* e)
{
    Core::OnAir* oa = Core::OnAir::cast(e);
    assert(0 != oa);
    Core::LogicObject* p = OWNER();
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
    Core::LogicObject* p = OWNER();
    assert(0 != p);
    if (os->object() != p) {
        return;
    }
    p->changeState(this, new OnGround());
}

Core::Command* Jumping::onInit()
{
    // TODO return command to change texture
    Base::EventManager::process(new MakeTriggerForPlatforms(OWNER(), true));
    return new Jump(OWNER(), 20 * m_power);
}

Core::Command* Jumping::command()
{
    assert(0 != OWNER()->component<Core::Physics>());
    if (OWNER()->component<Core::Physics>()->velocity().y() < 0) {
        OWNER()->changeState(this, new Falling);
        return 0;
    }
    if (0 == m_count) {
        return 0;
    }
    --m_count;
    return new Jump(OWNER(), m_power);
}

Falling::Falling()
{
    registerCallback<Core::OnSurface>(
            new Base::DelegateCreator<Falling>(this, &Falling::onSurface));
}

Core::Command* Falling::onInit()
{
    // TODO return command to change texture
    Base::EventManager::process(new MakeTriggerForPlatforms(OWNER(), false));
    return 0;
}

void Falling::onSurface(Base::Event* e)
{
    Core::OnSurface* os = Core::OnSurface::cast(e);
    assert(0 != os);
    Core::LogicObject* p = OWNER();
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
    registerCallback<LadderEnter>(
            new Base::DelegateCreator<Running>(this
                , &Running::onLadder));
}

void Running::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    assert(0 != key);
    Core::LogicObject* p = OWNER();
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
    LadderEnter* l = LadderEnter::cast(e);
    assert(0 != l);
    Core::LogicObject* p = OWNER();
    assert(0 != p);
    if (l->object() != p) {
        return;
    }
    p->addState(new NearLadder);
}

Core::Command* Running::onInit()
{
    // TODO return command to change texture and set direction
    assert(0 != OWNER());
    assert(0 != OWNER()->component<Core::TextureRenderer>());
    OWNER()->component<Core::TextureRenderer>()->setDirection(m_direction);
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
    return new ApplyMovement(OWNER(), 500, d);
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

SwitchInactive::SwitchInactive()
{
    registerCallback<AtTheSwitch>(
            new Base::DelegateCreator<SwitchInactive>(this
                , &SwitchInactive::atTheSwitch));
}

Core::Command* SwitchInactive::onInit()
{
    // TODO return command to change texture
    return 0;
}

void SwitchInactive::atTheSwitch(Base::Event* e)
{
    AtTheSwitch* as = AtTheSwitch::cast(e);
    assert(0 != as);
    if (as->switchObject() != OWNER()
            && as->status() == false) {
        return;
    }
    OWNER()->changeState(this, new SwitchActive);
}

SwitchActive::SwitchActive()
{
    registerCallback<AtTheSwitch>(
            new Base::DelegateCreator<SwitchActive>(this
                , &SwitchActive::atTheSwitch));
}

Core::Command* SwitchActive::onInit()
{
    // TODO return command to change texture
    return 0;
}

void SwitchActive::onKeyEvent(Base::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    assert(0 != key);
    Core::LogicObject* p = OWNER();
    assert(0 != p);
    if (key->mode() == Core::KeyEvent::Mode::Up
            || key->key() != Core::InputManager::Key::Up) {
        return;
    }
    Base::EventManager::process(new ToggleTheSwitch(p));
}

void SwitchActive::atTheSwitch(Base::Event* e)
{
    AtTheSwitch* as = AtTheSwitch::cast(e);
    assert(0 != as);
    if (as->switchObject() != OWNER()
            && as->status() == true) {
        return;
    }
    OWNER()->changeState(this, new SwitchInactive);
}

SwitchState::SwitchState(bool s)
    : m_status(s)
{
    registerCallback<ToggleTheSwitch>(
            new Base::DelegateCreator<SwitchState>(this
                , &SwitchState::onToggle));
}

Core::Command* SwitchState::onInit()
{
    // TODO return command to change texture
    assert(0 != OWNER());
    assert(0 != OWNER()->component<Core::TextureRenderer>());
    OWNER()->component<Core::TextureRenderer>()->setDirection((m_status)
            ? Core::HorizontalDirection::Left
            : Core::HorizontalDirection::Right);
    return 0;
}

void SwitchState::onToggle(Base::Event* e)
{
    ToggleTheSwitch* t = ToggleTheSwitch::cast(e);
    assert(0 != t);
    if (t->switchObject() != OWNER()) {
        return;
    }
    OWNER()->changeState(this, new SwitchState(!m_status));
}

} // namespace Assets
