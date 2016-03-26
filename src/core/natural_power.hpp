#ifndef _CORE_NATURAL_POWER_HPP_
#define _CORE_NATURAL_POWER_HPP_

#include "logic_object.hpp"

namespace Core
{

class NaturalPower : public Base::Object
{

public:
    virtual ~NaturalPower()
    {}

    virtual void init()
    {}

public:
    /**
     * @brief Interface for appling coresponding power to give logic object
     * @param l, pointe to logic object
     * @pre l should be valid pointer
     */
    virtual void applyToObject(LogicObject* l) = 0;
};

} // end of namespace Core

#endif // _CORE_NATURAL_POWER_HPP_
