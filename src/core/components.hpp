#ifndef _CORE_COMPONENTS_HPP_
#define _CORE_COMPONENTS_HPP_

#include "logic_object.hpp"
#include "shape.hpp"
#include "position.hpp"
#include "vector.hpp"

namespace Core
{

class Physics
    : public LogicObject::ComponentCreator<Physics> 
{
    Shape m_rect;
    Position m_position;
    int m_mass;
    Vector m_velocity;
    
public:
    inline void setRect(Shape rect)
    {
        m_rect = rect;
    }
    
    inline void setPosition(Position position)
    {
        m_position = position;
    }
    
    inline void setMass(int mass)
    {
        m_mass = mass;
    }

    inline void setVelocity(Vector velocity)
    {
        m_velocity = velocity;
    }

    inline void addVelocity(Vector velocity)
    {
        m_velocity += velocity;
    }

protected:
    void update();

};

} // namespace Core

#endif //_CORE_COMPONENTS_HPP_
