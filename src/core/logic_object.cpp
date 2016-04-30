#include "logic_object.hpp"
#include "logic.hpp"
#include "command.hpp"

#include <base/utility.hpp>

namespace Core
{

void LogicObject::update()
{
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->update();
    }
    for (const auto& state : children()) {
        Command* command = state->command();
        if (0 != command) {
            command->execute();
            delete command;
        }
    }
}

void LogicObject::addComponent(Component* component)
{
    assert(component != 0);
    component->setParent(this); // automatically set parent
    addObserver(component);
    m_components.insert(Components::value_type(component->getType()
                , component));
}

void LogicObject::changeState(State* oldState, State* newState)
{
    removeState(oldState);
    addState(newState);
}

void LogicObject::addState(State* newState)
{
    bool status = addObject(newState);
    assert(status);
    assert(0 != newState);
    newState->init();
    Base::Utility::ignoreUnused(status);
}

void LogicObject::removeState(State* state)
{
    bool status = removeObject(state);
    if (!status) {
        return;
    }
    assert(state != 0);
    state->deleteLater();
    Base::Utility::ignoreUnused(status);
}

void LogicObject::initObject()
{
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->init();
    }
}

void LogicObject::requestNewPosition(Position p)
{
    assert(0 != parent<Logic>());
    parent<Logic>()->updateObject(this, p);
}

LogicObject::LogicObject()
    : m_components()
    , m_position(Position())
{}

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
