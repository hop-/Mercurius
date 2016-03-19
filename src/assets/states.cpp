#include "states.hpp"
#include "commands.hpp"

#include <core/events.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>
#include <core/vector.hpp>
#include <core/input_manager.hpp>

namespace Assets
{

void Standing::process(Core::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    if (0 == key || key->mode() == Core::KeyEvent::Mode::Up) {
        return;
    }
    Core::LogicObject* p = parent<Core::LogicObject>();
    switch (key->key()) {
        case Core::InputManager::Key::Right:
        p->changeState(new RunningRight);
        break;
    case Core::InputManager::Key::Left:
        p->changeState(new RunningLeft);
    default:
        break;
    }
}

void Standing::init()
{
    // TODO change texture state
}

Core::Command* Standing::command() const
{
    assert(0 != parent<Core::LogicObject>());
    Core::Physics* ph =
        parent<Core::LogicObject>()->component<Core::Physics>();
    Core::Vector v;
    if (0 != ph) {
        v = ph->velocity();
        v.setAngle(v.angle() + 180);
    }
    return new Accelerate(parent<Core::LogicObject>(), v);
}

void RunningLeft::process(Core::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    if (0 == key) {
        return;
    }
    Core::LogicObject* p = parent<Core::LogicObject>();
    if (key->mode() == Core::KeyEvent::Mode::Down) {
        if (key->key() == Core::InputManager::Key::Right) {
            p->changeState(new RunningRight);
        }
    } else {
        if (key->key() == Core::InputManager::Key::Left) {
            p->changeState(new Standing);
        }
    }
}

void RunningLeft::init()
{
    // TODO change texture state
}

Core::Command* RunningLeft::command() const
{
    return new Accelerate(parent<Core::LogicObject>()
            , Core::Vector(1, 180));
}

void RunningRight::process(Core::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    if (0 == key) {
        return;
    }
    Core::LogicObject* p = parent<Core::LogicObject>();
    if (key->mode() == Core::KeyEvent::Mode::Down) {
        if (key->key() == Core::InputManager::Key::Left) {
            p->changeState(new RunningLeft);
        }
    } else {
        if (key->key() == Core::InputManager::Key::Right) {
            p->changeState(new Standing);
        }
    }
}

void RunningRight::init()
{
    // TODO change texture state
}

Core::Command* RunningRight::command() const
{
    return new Accelerate(parent<Core::LogicObject>()
            , Core::Vector(1, 0));
}

} // namespace Assets
