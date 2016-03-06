#ifndef _CORE_LOGIC_OBJECT_HPP_
#define _CORE_LOGIC_OBJECT_HPP_

#include "position.hpp"

#include <base/object.hpp>
#include <base/typed_base.hpp>

#include <map>
#include <cassert>

namespace Core
{

class Logic;

class LogicObject
    : public Base::Object
{
public:
    class Component
        : public Base::TypedBase
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

public:
    void update();
    virtual void init();
    void addComponent(Component* component);


    inline Position position() const
    {
        return m_position;
    }

    inline void setPosition(Position p)
    {
        m_position = p;
    }

    template <class T>
    inline T* component()
    {
        // TODO assert(static) if not exist T::type;
        assert(0 != m_components.at(T::type));
        return static_cast<T*>(m_components.at(T::type));
    }
};

template <class T>
const LogicObject::Component::ID LogicObject::ComponentCreator<T>::type;

template <class T>
LogicObject::ComponentCreator<T>::~ComponentCreator()
{}

} // namespace Core

#endif //_CORE_LOGIC_OBJECT_HPP_
