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
    int m_mass;
    Vector m_velocity;
    
public:
    inline Shape rect() const
    {
        return m_rect;
    }

    inline void setRect(const Shape& rect)
    {
        m_rect = rect;
    }
    
    inline Position position() const
    {
        return m_rect.position();
    }

    inline void setPosition(const Position& position)
    {
        m_rect.setPosition(position);
    }
    
    inline void setMass(int mass)
    {
        m_mass = mass;
    }

    inline void setVelocity(const Vector& velocity)
    {
        m_velocity = velocity;
    }

    inline void addVelocity(const Vector& velocity)
    {
        m_velocity += velocity;
    }

protected:
    void update();

};

} // namespace Core

#endif //_CORE_COMPONENTS_HPP_
