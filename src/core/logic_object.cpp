#include "logic_object.hpp"
#include "logic.hpp"
#include "components.hpp"
#include "command.hpp"

#include <base/utility.hpp>

namespace Core
{

LogicObject* LogicObject::Component::
parent() const
{
    return m_parent;
}

void LogicObject::Component::
setParent(LogicObject* parent)
{
    m_parent = parent;
    onParentSet();
}

Logic* LogicObject::Component::
logic()
{
    assert(0 != parent());
    assert(0 != parent()->parent<Logic>());
    return parent()->parent<Logic>();
}

Transform* LogicObject::Component::
transform()
{
    assert(0 != component<Transform>());
    return component<Transform>();
}

void LogicObject::
update()
{
    for (const auto& state : children()) {
        Command* command = state->command();
        if (0 != command) {
            command->execute();
            delete command;
        }
    }
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->update();
    }
}

void LogicObject::
addComponent(Component* component)
{
    assert(component != 0);
    component->setParent(this); // automatically set parent
    m_components.insert(Components::value_type(component->getType()
                , component));
}

void LogicObject::
changeState(State* oldState, State* newState)
{
    removeState(oldState);
    addState(newState);
}

std::string LogicObject::
typeName() const
{
    return m_typeName;
}

void LogicObject::
setTypeName(const std::string& typeName)
{
    m_typeName = typeName;
}

Position LogicObject::
position() const
{
    assert(component<Transform>());
    return component<Transform>()->position();
}

void LogicObject::
setPosition(Position p)
{
    assert(component<Transform>());
    component<Transform>()->setPosition(p);
}

void LogicObject::
setPosition(UserUnit x, UserUnit y)
{
    setPosition(Position(x, y));
}

float LogicObject::
scale() const
{
    assert(component<Transform>());
    return component<Transform>()->scaleFactor();
}

void LogicObject::
setScale(float scale)
{
    assert(component<Transform>());
    component<Transform>()->setScaleFactor(scale);
}

float LogicObject::
weight() const
{
    return m_weight;
}

void LogicObject::
setWeight(float w)
{
    m_weight = w;
}

void LogicObject::
addState(State* newState)
{
    bool status = addObject(newState);
    assert(status);
    assert(0 != newState);
    newState->init();
    Base::Utility::ignoreUnused(status);
}

void LogicObject::
removeState(State* state)
{
    bool status = removeObject(state);
    if (!status) {
        return;
    }
    assert(state != 0);
    state->deleteLater();
    Base::Utility::ignoreUnused(status);
}

void LogicObject::
initObject()
{
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->init();
    }
}

LogicObject::
LogicObject()
    : m_components()
{}

LogicObject::
~LogicObject()
{
    std::for_each(m_components.begin(), m_components.end(), [](Components::value_type v) {
        assert(0 != v.second);
        delete v.second;
    });
    m_components.clear();
    assert(m_components.empty());
}

} // namespace Core
