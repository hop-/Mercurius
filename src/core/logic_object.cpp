#include "logic_object.hpp"

namespace Core
{


LogicObject::LogicObject()
{
    init();
}

void LogicObject::update()
{
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->update();
    }
}

void LogicObject::addComponent(Component* component)
{
    assert(component != 0);
    m_components.insert(std::pair<int, Component*>(component->getType(), component));
}

void LogicObject::init()
{
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->init();
    }
}


} // namespace Core
