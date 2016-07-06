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

#include <debug/log.hpp>

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

    void setMovingArea(Rectangle area);
    Rectangle movingArea() const;
    void onNotify();

private:
    void aim();
    EngineUnit middleX() const;
    EngineUnit middleY() const;
    const LogicObject* target() const;

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
    float gravityScale() const;
    void setGravityScale(float gravityScale);
    Vector velocity() const;
    void setVelocity(const Vector& velocity);
    void addVelocity(const Vector& velocity);
    void applyGravity(const Vector& gravity);
    void stopX();
    void stopY();

private:
    void update();
    void onCollisionEnter(Base::Event* e);
    void onCollisionExit(Base::Event* e);

    bool isOnSurface();
};

class Collider
    : public LogicObject::ComponentCreator<Collider>
{
    using Objects = std::list<const LogicObject*>;

    EngineUnit m_width = 0;
    EngineUnit m_height = 0;
    Position m_offset = Position();
    bool m_isTrigger = false;
    Objects m_triggerObjects = Objects();
    float m_scaleFactor = 1;

public:
    void onNotify();
    void addTriggerObject(const LogicObject* object);
    void removeTriggerObject(const LogicObject* object);
    bool isTrigger(const LogicObject* object) const;
    Position position() const;
    Rectangle rect() const;
    void setOffset(Position offset);
    void setOffset(UserUnit x, UserUnit y);
    void setSizes(UserUnit width, UserUnit height);
    UserUnit width() const;
    UserUnit height() const;
    bool isTrigger() const;
    void trigger(bool isTrigger);

private:
    void onParentSet();
    void scaleSizes();
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
    EngineUnit m_width = 0;
    EngineUnit m_height = 0;

public:
    // TODO add some useful functions
    void setState(int state);
    virtual void onNotify() override;
    void setSizes(UserUnit w, UserUnit h);
    UserUnit width() const;
    UserUnit height() const;
    Rectangle rect() const;
    void setStateNumber(int numberOfStates);
    HorizontalDirection direction() const;
    float scaleFactor() const;
    void setDirection(HorizontalDirection d);
    int state() const;
    Position objectPosition() const;

private:
    void init();
    void onParentSet();
};

class ArrayObject
    : public LogicObject::ComponentCreator<ArrayObject>
{
    int m_rows = 1;
    int m_columns = 1;

public:
    int rows() const;
    void setRows(int rows);
    int columns() const;
    void setColumns(int columns);

private:
    void init();
};

} // namespace Core

#endif //_CORE_COMPONENTS_HPP_
