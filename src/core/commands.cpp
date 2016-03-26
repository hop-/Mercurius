#include "commands.hpp"
#include "logic_object.hpp"
#include "components.hpp"

#include <cassert>

namespace Core
{

Accelerate::Accelerate(Core::LogicObject* object, Core::Vector acceleration)
    : m_object(object)
    , m_acceleration(acceleration)
{
    assert(0 != m_object);
}

void Accelerate::execute()
{
    assert(0 != m_object);
    Core::Physics* physics = m_object->component<Core::Physics>();
    if (0 != physics) {
        physics->addVelocity(m_acceleration);
    }
}

Stand::Stand(Core::LogicObject* object)
    : m_object(object)
{
    assert(0 != m_object);
}

void Stand::execute()
{
    assert(0 != m_object);
    Core::Physics* physics = m_object->component<Core::Physics>();
    if (0 != physics) {
        Vector vel = physics->velocity();
        vel.setX(0);
        physics->setVelocity(vel);
    }
}

} // namespace Core
