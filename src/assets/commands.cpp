#include "commands.hpp"

#include <core/logic_object.hpp>
#include <core/components.hpp>

#include <cassert>

namespace Assets
{

Accelerate::Accelerate(Core::LogicObject* object, Core::Vector acceleration)
    : m_object(object)
    , m_acceleration(acceleration)
{}

void Accelerate::execute()
{
    assert(0 != m_object);
    Core::Physics* physics = m_object->component<Core::Physics>();
    if (0 != physics) {
        physics->addVelocity(m_acceleration);
    }
}

} // namespace Assets
