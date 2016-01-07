#ifndef _CORE_LOGIC_OBJECT_HPP_
#define _CORE_LOGIC_OBJECT_HPP_

#include "subject.hpp"

#include <vector>
#include <cassert>

namespace Core
{

class LogicObject
    : public Subject
{
public:
    class Component 
    {
        friend class LogicObject; // can be restructured
    public:
        virtual ~Component() = 0;
    private:
        virtual void update() {};
        virtual void init() {};
    };

private:
    std::vector<Component*> m_components;

public:
    LogicObject();

public:
    void update();
    void addComponent(Component* component);
    template <class T>
    T getComponent()
    {
        // TODO it is not lightweight implementation, must be lightweight
        for (Component* component : m_components) {
            T castedComponent = dynamic_cast<T>(component);
            if (castedComponent != 0) {
                return castedComponent;
            }
        }
        assert(!"No component of mentioned type.");
    }

private:
    void init();
};

} // namespace Core

#endif //_CORE_LOGIC_OBJECT_HPP_
