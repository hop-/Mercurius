#include "powers.hpp"
#include "components.hpp"

namespace Core
{

Vector Gravity::m_gravityVector = Vector(9.8, 270); // TODO 9.8 isn't valid

void Gravity::
applyToObject(LogicObject* lo)
{
    assert(0 != lo);
    Physics* ph = lo->component<Physics>();
    if (0 != ph) {
        ph->applyGravity(m_gravityVector);
    }
}

} // namespace Core
