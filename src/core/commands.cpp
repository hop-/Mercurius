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

SetYVelocity::SetYVelocity(LogicObject* object, EngineUnit v)
    : m_object(object)
    , m_yVelocity(v)
{}

void SetYVelocity::execute()
{
    assert(0 != m_object);
    Physics* physics = m_object->component<Physics>();
    if (0 != physics) {
        physics->setVelocity(Vector(physics->velocity().x(), m_yVelocity));
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
