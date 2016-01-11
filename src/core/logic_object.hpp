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
        LogicObject* m_parent;

    public:
        inline LogicObject* getParent()
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
    
        bool less(TypedBase* o) final
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

private:
    std::map<int, Component*> m_components;

public:
    void update();
    void init(); // may be this funtionality will assign to addComponent
    void addComponent(Component* component);
    template <class T>
    inline T* getComponent()
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
