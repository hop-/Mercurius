#include "dynamic_object.hpp"

namespace Core
{

void DynamicObject::addVector(Vector vector)
{
    m_velocity += vector;
}

} // namespace Core
