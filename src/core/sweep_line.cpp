#include "sweep_line.hpp"

#include "logic_object.hpp"
#include "components.hpp"

#include <cassert>

namespace Core
{


SweepLine::SweepLine()
    : m_sorted(false)
{}

SweepLine::~SweepLine()
{}

void SweepLine::insert(LogicObject* object)
{
    assert(0 != object);
    Rectangle rect = object->getComponent<Physics>()->rect();
    m_objects.push_back(std::pair<LogicObject*, Rectangle>(
                object, rect));
    if (!m_sorted) {
        return;
    }
    sortLastInserted();
}

void SweepLine::sort()
{
    EngineUnit pivotValue = m_objects[m_objects.size() / 2].second.xMin();
    
    m_sorted = true;
}

void SweepLine::sortLastInserted()
{
    std::pair<LogicObject*, Rectangle> key = m_objects.back();
    EngineUnit keyRectMinX = key.second.xMin();
    int i = static_cast<int>(m_objects.size());
    while (i != 0 && m_objects[i - 1].second.xMin() > keyRectMinX) {
        m_objects[i] = m_objects[i - 1];
        --i;
    }
    m_objects[i] = key;
}


} // namespace Core
