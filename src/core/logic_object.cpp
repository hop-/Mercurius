#include "logic_object.hpp"
#include "logic.hpp"
#include <iostream>

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

void LogicObject::changeState(State* newState)
{
    removeObject(m_currentState);
    addObject(newState);
}

void LogicObject::process(Event* event)
{
    std::vector<State*> states = children();
    for (auto currentState : states) {
        assert(0 != currentState);
        m_currentState = currentState;
        m_currentState->process(event);
    }
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
