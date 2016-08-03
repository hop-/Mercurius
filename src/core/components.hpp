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

class Transform
    : public LogicObject::ComponentCreator<Transform>
{
    Position m_position = Position();
    float m_scale = 1;

public:
    /**
     * @brief Returns position
     */
    Position position() const;

    /**
     * @brief Returns scaling factor
     */
    float scaleFactor() const;

    /**
     * @brief Sets position
     * @param p new Position
     */
    void setPosition(Position p);

    /**
     * @brief Sets scaleFactor
     * @param s float new scale factor
     */
    void setScaleFactor(float s);
};

class ViewPort
    : public Base::Singleton<ViewPort>
    , public LogicObject::ComponentCreator<ViewPort>
    , public Rectangle
{
    Rectangle m_movingArea;

private:
    /**
     * @brief Constructor to ViewPort component
     */
    ViewPort();

public:
    /**
     * @brief Sets target object for aim to
     * @param object pointer to LogicObject
     */
    void target(LogicObject* object);

    /**
     * @brief Sets moving area where view port can move
     * @param area Rectangle where view port can move
     */
    void setMovingArea(Rectangle area);

    /**
     * @brief Returns moving area
     * @return Rectangle
     */
    Rectangle movingArea() const;

    /**
     * @brief Notify function
     */
    void onNotify() override;

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
    /**
     * @brief Constructor to Physics Component
     */
    Physics();

public:
    // init function empty
    void init() {}

    /**
     * @brief Returns gravity sacling factor
     */
    float gravityScale() const;

    /**
     * @brief Sets gravity scaling factor
     * @param gravityScale float
     */
    void setGravityScale(float gravityScale);

    /**
     * @brief Returns velocity of object
     */
    Vector velocity() const;

    /**
     * @brief Sets velocity of object
     * @param velocity Vector of velocity
     */
    void setVelocity(const Vector& velocity);

    /**
     * @brief Adds velocity to the objects velosity
     * @param velocity Vector of velocity to add
     */
    void addVelocity(const Vector& velocity);

    /**
     * @brief Applies gravity to the object
     * @param gravity Vector of gravity
     */
    void applyGravity(const Vector& gravity);

    /**
     * @brief Sets 0 the X component of velocity
     */
    void stopX();

    /**
     * @brief Sets 0 the Y component of velocity
     */
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
    /**
     * @brief Adds new trigger object to trigger objects list
     * @param object valid const pointer to LogicObject
     */
    void addTriggerObject(const LogicObject* object);

    /**
     * @brief Removes object form trigger objects list
     * @param object valid const pointer to LogicObject
     */
    void removeTriggerObject(const LogicObject* object);

    /**
     * @brief Checks if given object is on tirgger objects list
     * @param object valid const pointer to LogicObject
     */
    bool isTrigger(const LogicObject* object) const;

    /**
     * @brief Returns Position of collider (object)
     */
    Position position() const;

    /**
     * @brief Return rectangle of collider
     */
    Rectangle rect() const;

    /**
     * @brief Sets offset of collider from ojbect
     * @param offset Position of collider if Object position is origin
     */
    void setOffset(Position offset);

    /**
     * @brief Sets offset of collider from ojbect
     * @param x UserUnit X position of collider if Object position is origin
     * @param y UserUnit Y position of collider if Object position is origin
     */
    void setOffset(UserUnit x, UserUnit y);

    /**
     * @brief Set Colliders sizes (width, height)
     * @param width UserUnit colliders width
     * @param height UserUnit colliders width
     */
    void setSizes(UserUnit width, UserUnit height);

    /**
     * @brief Returns colliders width
     */
    UserUnit width() const;

    /**
     * @brief Returns colliders height
     */
    UserUnit height() const;

    /**
     * @brief Checks if collider is trigger type
     */
    bool isTrigger() const;

    /**
     * @brief Sets the weather Collider is trigger or not
     */
    void trigger(bool isTrigger);

private:
    void onParentSet();
    void scaleSizes();
};

class TextureRenderer
    : public LogicObject::ComponentCreator<TextureRenderer>
{
    unsigned m_state = 0;
    int m_numberOfStates = 1;
    float m_scaleFactor = 1;
    Position m_position = Position();
    HorizontalDirection m_direction = HorizontalDirection::Right;
    EngineUnit m_width = 0;
    EngineUnit m_height = 0;

public:
    /**
     * @brief Initializing component
     */
    void init() override;

    /**
     * @brief Sets the state (drawing state)
     * @param state int
     */
    void setState(int state);

    /**
     * @brief Notify function
     */
    void onNotify() override;

    /**
     * @brief Sets the sizes of Texture
     * @param w UserUnit width
     * @param h UserUnit height
     */
    void setSizes(UserUnit w, UserUnit h);

    /**
     * @brief Returns textureRenderes width
     */
    UserUnit width() const;

    /**
     * @brief Returns textureRenderes height
     */
    UserUnit height() const;

    /**
     * @brief Returns rectangle of textureRenderes
     */
    Rectangle rect() const;

    /**
     * @brief Sets the number of states
     * @param numberOfStates int number of states
     */
    void setStateNumber(int numberOfStates);

    /**
     * @brief Returns direction of texture
     */
    HorizontalDirection direction() const;

    /**
     * @brief Returns scaling factor
     */
    float scaleFactor() const;

    /**
     * @brief Sets dirrection of texture
     * @param d HorizontalDirection
     */
    void setDirection(HorizontalDirection d);

    /**
     * @brief Returns state
     */
    int state() const;

    /**
     * @brief Returns object position
     */
    Position objectPosition() const;

private:
    /**
     * @brief Function which calls when parent is already set
     */
    void onParentSet();
};

class ArrayObject
    : public LogicObject::ComponentCreator<ArrayObject>
{
    int m_rows = 1;
    int m_columns = 1;

public:
    /**
     * @brief Returns number of rows
     */
    int rows() const;

    /**
     * @brief Sets number of rows
     */
    void setRows(int rows);

    /**
     * @brief Returns number of colunms
     */
    int columns() const;

    /**
     * @brief Sets number of coluums
     */
    void setColumns(int columns);

private:
    void init();
};

class Animator
    : public LogicObject::ComponentCreator<Animator>
{
    unsigned m_frameDelay = 1;

public:
    /**
     * @brief constructor to Animator class
     */
    Animator();

public:
    /**
     * @brief Sets frame rate
     * @param rate int new frame rate
     */
     void setFrameRate(int rate);

    //setState(state) //animation state
    // TODO add needed functionality
};

} // namespace Core

#endif //_CORE_COMPONENTS_HPP_
