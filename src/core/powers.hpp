#ifndef _CORE_POWER_HPP_
#define _CORE_POWER_HPP_

#include "natural_power.hpp"
#include "components.hpp"

namespace Core
{

class Gravity : public NaturalPower
{
public:
    /// Reimplemented interface
    virtual void applyToObject(LogicObject* lo)
    {
        assert(0 != lo);
        Physics* ph = lo->component<Physics>();
        if (ph != 0 && 0 != lo->weight()) {
            ph->addVelocity(Vector(9.8, 270));
        }
    }
};

} // end of namespace Core

#endif // _CORE_POWER_HPP_
