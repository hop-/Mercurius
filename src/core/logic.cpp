#include "logic.hpp"
#include "logic_object.hpp"

#include <algorithm>

namespace Core
{

void Logic::update()
{
    for (auto* object : m_objects) {
        assert(0 != object);
        object->update();
    }
}

void Logic::addLogicObject(LogicObject* o)
{
    assert(0 != o);
    assert(m_objects.end() ==
           std::find(m_objects.begin(), m_objects.end(), o));
    m_objects.push_back(o);
}

void Logic::removeLogicObject(LogicObject* o)
{
    assert(0 != o);
    LogicObjects::iterator i =
        std::find(m_objects.begin(), m_objects.end(), o);
    assert(m_objects.end() != i);
    m_objects.erase(i);
}

Logic::~Logic()
{
}

} // namespace Core 
