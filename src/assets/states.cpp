#include "states.hpp"

#include <core/events.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>
#include <core/vector.hpp>

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
    case 1073741903:
        p->component<Core::Physics>()->setVelocity(Core::Vector(1, 0));
        p->changeState(new RunningRight);
        break;
    case 1073741904:
        p->component<Core::Physics>()->setVelocity(Core::Vector(1, 180));
        p->changeState(new RunningLeft);
    default:
        break;
    }
}

void RunningLeft::process(Core::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    if (0 == key || key->mode() == Core::KeyEvent::Mode::Down) {
        return;
    }
    Core::LogicObject* p = parent<Core::LogicObject>();
    if (key->key() == 1073741904) {
        p->component<Core::Physics>()->setVelocity(Core::Vector(0, 0));
        p->changeState(new Standing);
    }
}

void RunningRight::process(Core::Event* e)
{
    Core::KeyEvent* key = Core::KeyEvent::cast(e);
    if (0 == key || key->mode() == Core::KeyEvent::Mode::Down) {
        return;
    }
    Core::LogicObject* p = parent<Core::LogicObject>();
    if (key->key() == 1073741903) {
        p->component<Core::Physics>()->setVelocity(Core::Vector(0, 0));
        p->changeState(new Standing);
    }
}

} // namespace Assets
