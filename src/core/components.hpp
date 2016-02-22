#ifndef _CORE_COMPONENTS_HPP_
#define _CORE_COMPONENTS_HPP_

#include "logic_object.hpp"
#include "position.hpp"
#include "rectangle.hpp"
#include "vector.hpp"

#include <base/subject.hpp>

namespace Core
{

class ViewPort
    : LogicObject::ComponentCreator<ViewPort>
    , Rectangle
{
    LogicObject* m_targetObject;

public:
    void target(LogicObject* object);
    
private:
    void aim();
    void update();
};

class Dimensions    // for now it have no any use in codes
                    // may be it will removed in future
    : public LogicObject::ComponentCreator<Dimensions>
{
    Position m_position;
    float m_scale;

public:
    inline Position position() const
    {
        return m_position;
    }

    inline void setPosition(Position position)
    {
        m_position = position;
    }

    inline float scale() const
    {
        return m_scale;
    }

    inline void setScale(float scale)
    {
        m_scale = scale;
    }
};

class Physics
    : public LogicObject::ComponentCreator<Physics> 
{
    int m_mass;
    Vector m_velocity;
    
public:
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

private:
    void update();

};

class Collider
    : public LogicObject::ComponentCreator<Collider>
{
    EngineUnit m_width;
    EngineUnit m_height;

public:
    inline Rectangle rect() const
    {
        return Rectangle(m_width, m_height, parent()->position());
    }

    inline void setSizes(EngineUnit width, EngineUnit height)
    {
        m_width = width;
        m_height = height;
    }
    
};

class TextureRenderer
    : public LogicObject::ComponentCreator<TextureRenderer>
    , public Base::Subject
{
    // think it should have some info about texture
    unsigned m_state;
    int m_numberOfStates;

public:
    // TODO add some useful functions
    void setState(int state);

    inline void setStateNumber(int numberOfStates)
    {
        m_numberOfStates = 0;
    }

    inline int state() const
    {
        return static_cast<int>(m_state);
    }

private:
    void init();
};

} // namespace Core

#endif //_CORE_COMPONENTS_HPP_
