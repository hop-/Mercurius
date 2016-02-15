#include "logic_object.hpp"
#include "logic.hpp"

namespace Core
{

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
    component->setParent(this); // automatically set parent
    m_components.insert(std::pair<int, Component*>(component->getType(), component));
}

void LogicObject::init()
{
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->init();
    }
}

LogicObject::LogicObject(Logic* parent)
    : m_parent(parent)
{
    assert(parent != 0);
    parent->addLogicObject(this);
}

} // namespace Core
