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
    class GravityComponent : public LogicObject::ComponentCreator<GravityComponent>
    {
    EngineUnit m_v = 0;

    public:
        virtual void update()
        {
            m_v = m_v + 9.8; // TODO v = v0 + g*t^2 / 2
            assert(0 != parent());
            Physics* ph = parent()->component<Physics>();
            if (ph != 0 && 0 != parent()->weight()) {
/*                Position position = parent()->position();
                position.move(Vector(m_v, 270));
                parent()->setPosition(position);*/
                ph->addVelocity(Vector(9.8, 270));
            }
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
