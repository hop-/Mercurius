#ifndef _CORE_POWER_HPP_
#define _CORE_POWER_HPP_

#include "natural_power.hpp"
#include "components.hpp"

#include <iostream>

namespace Core
{

class Gravity : public NaturalPower
{
public:
    class GravityComponent : public LogicObject::ComponentCreator<Physics>
    {
    public:
        virtual void update()
        {
            // TODO update postion
        }
    };

public:
    Gravity()
    {
        setComponentCreator(new GravityFactory()); // TODO fixe the bug and move to init
    }

    virtual void init()
    {
    }

private:
    class GravityFactory : public NaturalPower::ComponentAbstractFactory
    {
    public:
        virtual LogicObject::Component* createComponent()
        {
            return new GravityComponent();
        }
    };
};

} // end of namespace Core

#endif // _CORE_POWER_HPP_
