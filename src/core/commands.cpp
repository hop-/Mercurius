#include "commands.hpp"
#include "logic_object.hpp"
#include "components.hpp"

#include <cassert>

namespace Core
{

Accelerate::Accelerate(LogicObject* object, Vector acceleration)
    : m_object(object)
    , m_acceleration(acceleration)
{
    assert(0 != m_object);
}

void Accelerate::execute()
{
    assert(0 != m_object);
    Physics* physics = m_object->component<Physics>();
    if (0 != physics) {
        physics->addVelocity(m_acceleration);
    }
}

Stop::Stop(LogicObject* object, Direction d)
    : m_object(object)
    , m_direction(d)
{
    assert(0 != m_object);
}

void Stop::execute()
{
    assert(0 != m_object);
    Physics* physics = m_object->component<Physics>();
    if (0 == physics) {
        return;
    }
    switch (m_direction) {
    case Direction::Up:
        if (physics->velocity().y() > 0) {
            physics->stopY();
        }
        break;
    case Direction::Down:
        if (physics->velocity().y() < 0) {
            physics->stopY();
        }
        break;
    case Direction::Left:
        if (physics->velocity().x() < 0) {
            physics->stopX();
        }
        break;
    case Direction::Right:
        if (physics->velocity().x() > 0) {
            physics->stopX();
        }
    default:
        break;
    }
}

SetYVelocity::SetYVelocity(LogicObject* object, EngineUnit v, VerticalDirection d)
    : m_object(object)
    , m_yVelocity(v)
    , m_direction(d)
{
    assert(0 != m_object);
}

void SetYVelocity::execute()
{
    assert(0 != m_object);
    Physics* physics = m_object->component<Physics>();
    if (0 != physics) {
        physics->setVelocity(Vector(m_yVelocity, (m_direction == VerticalDirection::Up) ? 90: 270));
    }
}

Jump::Jump(LogicObject* object, EngineUnit power)
    : m_object(object)
    , m_power(power)
{}

void Jump::execute()
{
    assert(0 != m_object);
    Physics* physics = m_object->component<Physics>();
    if (0 != physics) {
        physics->addVelocity(Vector(m_power, 90));
    }
}

Stand::Stand(LogicObject* object)
    : m_object(object)
{
    assert(0 != m_object);
}

void Stand::execute()
{
    assert(0 != m_object);
    Physics* physics = m_object->component<Physics>();
    if (0 != physics) {
        Vector vel = physics->velocity();
        vel.setX(0);
        physics->setVelocity(vel);
    }
}

} // namespace Core
