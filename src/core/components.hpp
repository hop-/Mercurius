#ifndef _CORE_COMPONENTS_HPP_
#define _CORE_COMPONENTS_HPP_

#include "logic_object.hpp"
#include "position.hpp"
#include "rectangle.hpp"
#include "vector.hpp"
#include "units.hpp"

#include <base/subject.hpp>

namespace Core
{

class ViewPort
    : public LogicObject::ComponentCreator<ViewPort>
    , public Rectangle
    , public Base::Subject
{
    Rectangle m_movingArea;

public:
    ViewPort();

public:
    void target(LogicObject* object);

    inline void setMovingArea(Rectangle area)
    {
        m_movingArea = area;
    }

    Rectangle movingArea()
    {
        return m_movingArea;
    }

    void onNotify();

private:
    void aim();

    inline EngineUnit middleX()
    {
        return (xMax() - xMin()) / 2;
    }

    inline EngineUnit middleY()
    {
        return (yMax() - yMin()) / 2;
    }

    inline const LogicObject* target() const
    {
         return static_cast<const LogicObject*>(subject());
    }
};

class Physics
    : public LogicObject::ComponentCreator<Physics>
{
    int m_mass;
    Vector m_velocity;

public:
    inline int mass() const
    {
        return m_mass;
    }

    inline Vector velocity()
    {
        return m_velocity;
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

private:
    void update();

};

class Collider
    : public LogicObject::ComponentCreator<Collider>
{
    EngineUnit m_width;
    EngineUnit m_height;
    bool m_isTrigger = false;

public:
    void onNotify();

    inline Rectangle rect() const
    {
        return Rectangle(m_width, m_height, parent()->position());
    }

    inline void setSizes(UserUnit width, UserUnit height)
    {
        m_width = width;
        m_height = height;
    }

    inline bool isTrigger() const
    {
        return m_isTrigger;
    }

    inline void trigger(bool isTrigger)
    {
        m_isTrigger = isTrigger;
    }
};

class TextureRenderer
    : public LogicObject::ComponentCreator<TextureRenderer>
    , public Base::Subject
{
    unsigned m_state = 0;
    int m_numberOfStates = 1;
    float m_scaleFactor = 1;
    Position m_position;

public:
    // TODO add some useful functions
    void setState(int state);
    void onNotify();

    inline void setStateNumber(int numberOfStates)
    {
        m_numberOfStates = 0;
    }

    inline void setScaleFactor(float scaleFactor)
    {
        m_scaleFactor = scaleFactor;
    }

    inline float scaleFactor() const
    {
        return m_scaleFactor;
    }

    inline int state() const
    {
        return static_cast<int>(m_state);
    }

    inline Position objectPosition() const
    {
        return parent()->position();
    }

private:
    void init();
};

} // namespace Core

#endif //_CORE_COMPONENTS_HPP_
