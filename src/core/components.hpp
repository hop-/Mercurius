#ifndef _CORE_COMPONENTS_HPP_
#define _CORE_COMPONENTS_HPP_

#include "logic_object.hpp"
#include "position.hpp"
#include "rectangle.hpp"
#include "vector.hpp"
#include "units.hpp"

#include <base/singleton.hpp>
#include <base/subject.hpp>
#include <base/object.hpp>

#include <list>

namespace Base
{

class Event;

}

namespace Core
{

class ViewPort
    : public Base::Singleton<ViewPort>
    , public LogicObject::ComponentCreator<ViewPort>
    , public Rectangle
    , public Base::Subject
{
    Rectangle m_movingArea;

private:
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
        return (right() - left()) / 2;
    }

    inline EngineUnit middleY()
    {
        return (top() - bottom()) / 2;
    }

    inline const LogicObject* target() const
    {
         return static_cast<const LogicObject*>(subject());
    }

private:
    friend class Base::Singleton<ViewPort>;
};

class Physics
    : public LogicObject::ComponentCreator<Physics>
    , public Base::Object
{
    float m_gravityScale = 1;
    Vector m_velocity = Vector();
    std::list<const LogicObject*> m_grounds;

public:
    Physics();

public:
    void init() {}

    inline float gravityScale() const
    {
        return m_gravityScale;
    }

    inline void setGravityScale(float gravityScale)
    {
        m_gravityScale = gravityScale;
    }

    inline Vector velocity()
    {
        return m_velocity;
    }

    inline void setVelocity(const Vector& velocity)
    {
        m_velocity = velocity;
    }

    inline void addVelocity(const Vector& velocity)
    {
        m_velocity += velocity;
    }

    inline void applyGravity(const Vector& gravity)
    {
        if (isOnSurface()) {
            return;
        }
        m_velocity += gravity * m_gravityScale;
    }

    inline void stopX()
    {
        Vector v = m_velocity;
        v.setX(0);
        setVelocity(v);
    }

    inline void stopY()
    {
        Vector v = m_velocity;
        v.setY(0);
        setVelocity(v);
    }

private:
    void update();
    void onCollisionEnter(Base::Event* e);
    void onCollisionExit(Base::Event* e);

    bool isOnSurface() {
        return m_grounds.size();
    }
};

class Collider
    : public LogicObject::ComponentCreator<Collider>
{
    using Objects = std::list<const LogicObject*>;

    EngineUnit m_width = 0;
    EngineUnit m_height = 0;
    bool m_isTrigger = false;
    Objects m_triggerObjects = Objects();
    float m_scaleFactor = 1;

public:
    void onNotify();
    void addTriggerObject(const LogicObject* object);
    void removeTriggerObject(const LogicObject* object);
    bool isTrigger(const LogicObject* object) const;

    inline Rectangle rect() const
    {
        return Rectangle(m_width, m_height, parent()->position());
    }

    inline void setSizes(UserUnit width, UserUnit height)
    {
        m_width = width;
        m_height = height;
        scaleSizes();
    }

    inline bool isTrigger() const
    {
        return m_isTrigger;
    }

    inline void trigger(bool isTrigger)
    {
        m_isTrigger = isTrigger;
    }

private:
    void onParentSet();

    void scaleSizes()
    {
        m_width = m_width * float(m_scaleFactor);
        m_height = m_height * float(m_scaleFactor);
    }
};

class TextureRenderer
    : public LogicObject::ComponentCreator<TextureRenderer>
    , public Base::Subject
{
    unsigned m_state = 0;
    int m_numberOfStates = 1;
    float m_scaleFactor = 1;
    Position m_position = Position();
    HorizontalDirection m_direction = HorizontalDirection::Right;

public:
    // TODO add some useful functions
    void setState(int state);
    void onNotify();

    inline void setStateNumber(int numberOfStates)
    {
        m_numberOfStates = numberOfStates;
    }

    inline HorizontalDirection direction() const
    {
        return m_direction;
    }

    inline float scaleFactor() const
    {
        return m_scaleFactor;
    }

    inline void setDirection(HorizontalDirection d)
    {
        m_direction = d;
        notify();
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
    void onParentSet();
};

} // namespace Core

#endif //_CORE_COMPONENTS_HPP_
