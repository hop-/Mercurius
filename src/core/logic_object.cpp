#include "logic_object.hpp"
#include "logic.hpp"

#include <algorithm>

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
    addObserver(component);
    m_components.insert(std::pair<int, Component*>(component->getType()
                , component));
}

void LogicObject::initObject()
{
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->init();
    }
}

LogicObject::LogicObject()
{
}

LogicObject::~LogicObject()
{
    std::for_each(m_components.begin(), m_components.end(), [](Components::value_type v) {
        assert(0 != v.second);
        delete v.second;
    });
    m_components.clear();
    assert(m_components.empty());
}

} // namespace Core
