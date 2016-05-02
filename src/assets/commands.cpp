#include "commands.hpp"

#include <core/logic_object.hpp>
#include <core/components.hpp>

#include <cassert>

namespace Assets
{

Accelerate::Accelerate(Core::LogicObject* object, Core::Vector acceleration)
    : Core::Command(object)
    , m_acceleration(acceleration)
{
}

void Accelerate::execute()
{
    assert(0 != object());
    Core::Physics* physics = object()->component<Core::Physics>();
    if (0 != physics) {
        physics->addVelocity(m_acceleration);
    }
}

Stop::Stop(Core::LogicObject* object, Core::Direction d)
    : Core::Command(object)
    , m_direction(d)
{
}

void Stop::execute()
{
    assert(0 != object());
    Core::Physics* physics = object()->component<Core::Physics>();
    if (0 == physics) {
        return;
    }
    switch (m_direction) {
    case Core::Direction::Up:
        if (physics->velocity().y() > 0) {
            physics->stopY();
        }
        break;
    case Core::Direction::Down:
        if (physics->velocity().y() < 0) {
            physics->stopY();
        }
        break;
    case Core::Direction::Left:
        if (physics->velocity().x() < 0) {
            physics->stopX();
        }
        break;
    case Core::Direction::Right:
        if (physics->velocity().x() > 0) {
            physics->stopX();
        }
    default:
        break;
    }
}

SetYVelocity::SetYVelocity(Core::LogicObject* object, Core::EngineUnit v, Core::VerticalDirection d)
    : Core::Command(object)
    , m_yVelocity(v)
    , m_direction(d)
{
}

void SetYVelocity::execute()
{
    assert(0 != object());
    Core::Physics* physics = object()->component<Core::Physics>();
    if (0 != physics) {
        physics->setVelocity(Core::Vector(m_yVelocity, (m_direction == Core::VerticalDirection::Up) ? 90: 270));
    }
}

Jump::Jump(Core::LogicObject* object, Core::EngineUnit power)
    : Core::Command(object)
    , m_power(power)
{
}

void Jump::execute()
{
    assert(0 != object());
    Core::Physics* physics = object()->component<Core::Physics>();
    if (0 != physics) {
        physics->addVelocity(Core::Vector(m_power, 90));
    }
}

Stand::Stand(Core::LogicObject* object)
    : Core::Command(object)
{
}

void Stand::execute()
{
    assert(0 != object());
    Core::Physics* physics = object()->component<Core::Physics>();
    if (0 != physics) {
        Core::Vector vel = physics->velocity();
        vel.setX(0);
        physics->setVelocity(vel);
    }
}

} // namespace Assets
