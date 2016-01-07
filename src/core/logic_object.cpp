#include "logic_object.hpp"

namespace Core
{


LogicObject::LogicObject()
{
    init();
}

void LogicObject::update()
{
    for (Component* component : m_components) {
        component->update();
    }
}

void LogicObject::addComponent(Component* component)
{
    assert(component != 0);
    m_components.push_back(component);
}

void LogicObject::init()
{
    for (Component* component : m_components) {
        component->init();
    }
}

} // namespace Core
