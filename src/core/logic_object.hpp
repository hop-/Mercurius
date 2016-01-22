#ifndef _CORE_LOGIC_OBJECT_HPP_
#define _CORE_LOGIC_OBJECT_HPP_

#include "typed_base.hpp"

#include "position.hpp"

#include <map>
#include <cassert>

namespace Core
{

class LogicObject
{
public:
    class Component
        : public TypedBase
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
    Position m_position;
    float m_scale;

public:
    void update();
    void init(); // may be this funtionality will assign to addComponent
    void addComponent(Component* component);


    inline Position position() const
    {
        return m_position;
    }

    inline void setPosition(Position p)
    {
        m_position = p;
    }

    inline float scale() const
    {
        return m_scale;
    }

    inline void setScale(float scale)
    {
        m_scale = scale;
    }

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
