#include "states.hpp"

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
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    p->component<Core::Physics>()->setVelocity(Core::Vector(0, 0));
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
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    p->component<Core::Physics>()->setVelocity(Core::Vector(1, 180));
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
    Core::LogicObject* p = parent<Core::LogicObject>();
    assert(0 != p);
    p->component<Core::Physics>()->setVelocity(Core::Vector(1, 0));
}

} // namespace Assets
