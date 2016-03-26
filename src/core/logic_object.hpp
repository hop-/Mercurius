#ifndef _CORE_LOGIC_OBJECT_HPP_
#define _CORE_LOGIC_OBJECT_HPP_

#include "position.hpp"
#include "state.hpp"

#include <base/container_object.hpp>
#include <base/subject.hpp>
#include <base/observer.hpp>
#include <base/typed_base.hpp>

#include <map>
#include <cassert>

namespace Core
{

class Logic;

class LogicObject
    : public Base::ContainerObject<State>
    , public Base::Subject
{
public:
    class Component
        : public Base::TypedBase
        , public Base::Observer
    {
        friend class LogicObject;
        LogicObject* m_parent;

    public:
        inline LogicObject* parent() const
        {
            return m_parent;
        }

        inline void setParent(LogicObject* parent)
        {
            m_parent = parent;
        }

        void onNotify(){}

    protected:
        virtual void update() {};
        virtual void init() {};

        bool less(Base::TypedBase* o) final
        {
            return false;
        }
    };

public:
    template <class T>
    class ComponentCreator
        : public Component
    {
    public:
        static const ID type;
        virtual ~ComponentCreator() = 0;

    public:
        int getType() const final
        {
            return type;
        }
    };

public:
    LogicObject();
    virtual ~LogicObject();

private:
    typedef std::map<int, Component*> Components;
    Components m_components;
    Position m_position;
    State* m_currentState = 0;
    float m_weight = 0;

public:
    void update();
    virtual void initObject();
    void addComponent(Component* component);
    void addState(State* newState);
    void changeState(State* newState);
    void removeState(State* state);
    void process(Event* event);
    void requestNewPosition(Position p);

    inline Position position() const
    {
        return m_position;
    }

    inline void setPosition(Position p)
    {
        m_position = p;
        notify();
    }


    inline float weight() const
    {
        return m_weight;
    }

    inline void setWeight(float w)
    {
        m_weight = w;
        notify();
    }

    inline void setPosition(UserUnit x, UserUnit y)
    {
        setPosition(Position(x, y));
    }

    template <class T>
    inline T* component() const
    {
        Components::const_iterator i = m_components.find(T::type);
        if (i == m_components.end()) {
            return 0;
        }
        return static_cast<T*>(i->second);
    }
};

template <class T>
const LogicObject::Component::ID LogicObject::ComponentCreator<T>::type;

template <class T>
LogicObject::ComponentCreator<T>::~ComponentCreator()
{}

} // namespace Core

#endif //_CORE_LOGIC_OBJECT_HPP_
