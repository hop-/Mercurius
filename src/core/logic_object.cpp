#include "logic_object.hpp"

namespace Core
{


void LogicObject::update()
{
<<<<<<< HEAD
    for (Component* component : m_components) {
        assert(component != 0);
        component->update();
=======
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->update();
>>>>>>> cc34d4e70a4142408082416afcf5d1e4f7a8fa3a
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
<<<<<<< HEAD
    for (Component* component : m_components) {
        assert(component != 0);
        component->init();
=======
    for (auto& pair : m_components) {
        assert(0 != pair.second);
        pair.second->init();
>>>>>>> cc34d4e70a4142408082416afcf5d1e4f7a8fa3a
    }
}


} // namespace Core
