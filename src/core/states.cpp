#include "states.hpp"
#include "commands.hpp"
#include "events.hpp"
#include "logic_object.hpp"
#include "components.hpp"
#include "vector.hpp"
#include "input_manager.hpp"

namespace Core
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
    return new Stand(parent<Core::LogicObject>());
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

} // namespace Core
