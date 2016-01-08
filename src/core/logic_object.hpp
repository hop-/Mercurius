#ifndef _CORE_LOGIC_OBJECT_HPP_
#define _CORE_LOGIC_OBJECT_HPP_

#include "subject.hpp"
#include "typed_base.hpp"

#include <map>
#include <cassert>

namespace Core
{

class LogicObject
    : public Subject
{
public:
    class Component
        : public TypedBase
    {
        friend class LogicObject;

    private:
        virtual void update() {};
        virtual void init() {};

        bool less(TypedBase* o)
        {
            return false; 
        }
    };

    template <class T>
    class ComponentCreator
        : public Component
    {
        static const ID type;

    public:
        virtual ~ComponentCreator() = 0;

    private:
        int getType() const
        {
            return type;
        }
    };

private:
    std::map<int, Component*> m_components;

public:
    LogicObject();

public:
    void update();
    void addComponent(Component* component);
    template <class T>
    inline T getComponent()
    {
        // TODO assert(static) if not exist T::type();
        assert(0 != m_components.at(T::type()));
        return static_cast<T>(m_components.at(T::type()));
    }

private:
    void init();
};

template <class T>
LogicObject::ComponentCreator<T>::~ComponentCreator()
{}

} // namespace Core

#endif //_CORE_LOGIC_OBJECT_HPP_
