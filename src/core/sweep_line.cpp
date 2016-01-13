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
    quickSort(0, m_objects.size());
    m_sorted = true;
}

void SweepLine::quickSort(int left, int right)
{
    int i = left;
    int j = right;
    std::pair<LogicObject*, Rectangle> tmp;
    EngineUnit pivotValue = m_objects[(left + right) / 2].second.xMin();
    while (i <= j) {
        while (m_objects[i].second.xMin() < pivotValue) {
            ++i;
        }
        while (m_objects[j].second.xMin() > pivotValue) {
            --j;
        }
        if (i <= j) {
            tmp = m_objects[i];
            m_objects[i] = m_objects[j];
            m_objects[j] = tmp;
            ++i;
            --j;
        }
    }
    if (left < j) {
        quickSort(left, j);
    }
    if (i < right) {
        quickSort(i, right);
    }
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
