#ifndef _CORE_POWER_HPP_
#define _CORE_POWER_HPP_

#include "natural_power.hpp"

namespace Core
{

class Gravity
    : public NaturalPower
{
    static Vector m_gravityVector;

public:
    /// Reimplemented interface
    void applyToObject(LogicObject* lo) final;
};

} // namespace Core

#endif // _CORE_POWER_HPP_
