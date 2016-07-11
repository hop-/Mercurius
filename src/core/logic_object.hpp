#ifndef _CORE_LOGIC_OBJECT_HPP_
#define _CORE_LOGIC_OBJECT_HPP_

#include "position.hpp"
#include "state.hpp"

#include <base/container_object.hpp>
#include <base/subject.hpp>
#include <base/observer.hpp>
#include <base/typed_base.hpp>

#include <string>
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
        LogicObject* m_parent = 0;

    public:
        LogicObject* parent() const; // TODO return type is not const
        void setParent(LogicObject* parent);
        void onNotify(){}

        template <class T>
        T* component()
        {
            return m_parent->component<T>();
        }

    protected:
        virtual void update() {};
        virtual void init() {};
        virtual void onParentSet() {};
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
    LogicObject(const LogicObject&) = delete;
    LogicObject& operator=(const LogicObject&) = delete;

private:
    typedef std::map<int, Component*> Components;

private:
    Components m_components;
    State* m_currentState = 0;
    float m_weight = 0; // TODO need to be removed
    std::string m_typeName = "";

public:
    void update();
    virtual void initObject();
    void addComponent(Component* component);
    void addState(State* newState);
    void changeState(State* oldState, State* newState);
    void removeState(State* state);
    void requestNewPosition(Position p);
    std::string typeName() const;
    void setTypeName(const std::string& typeName);
    Position position() const;
    void setPosition(Position p);
    float scale() const;
    void setScale(float scale);
    void setPosition(UserUnit x, UserUnit y);
    float weight() const;       // TODO remove
    void setWeight(float w);    //TODO remove

public:
    template <class T>
    T* component() const
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
