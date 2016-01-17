#include "sweep_line.hpp"

#include "logic_object.hpp"
#include "components.hpp"

#include <set>
#include <cmath>
#include <cassert>

namespace Core
{


// SweepLine::RectangleEdge

int SweepLine::RectangleEdge::m_currentIndex = 0;

SweepLine::RectangleEdge::RectangleEdge(int index
        , LogicObject* object, EngineUnit position, bool isBegin)
    : m_index(index)
    , m_object(object)
    , m_position(position)
    , m_begin(isBegin)
{}

void SweepLine::RectangleEdge::generate(SweepLine& parent
        , LogicObject* object)
{
    assert(0 != object);
    parent.insert(RectangleEdge(m_currentIndex, object
                , object->getComponent<Physics>()->rect().xMin(), true));
    parent.insert(RectangleEdge(m_currentIndex, object
                , object->getComponent<Physics>()->rect().xMax(), false));
    ++m_currentIndex;
}

// SweepLine::Interval

SweepLine::Interval::Interval(int nIndex, LogicObject* nObject
        , EngineUnit nMin, EngineUnit nMax)
    : index(nIndex)
    , object(nObject)
    , min(nMin)
    , max(nMax)
{}

bool SweepLine::Interval::intersect(const Interval& interval) const
{
    EngineUnit d1 = interval.min - max;
    EngineUnit d2 = min - interval.max;
    return (d1 < 0 && d2 < 0);
}

// SweepLine

SweepLine::SweepLine()
    : m_sorted(false)
{}

SweepLine::~SweepLine()
{}

void SweepLine::insert(LogicObject* object)
{
    assert(0 != object);
    RectangleEdge::generate(*this, object);
}

void SweepLine::insert(const RectangleEdge& object)
{
    m_objects.push_back(object);
    if (m_sorted) {
        sortLastInserted();
    }
}

std::vector<std::pair<LogicObject*, LogicObject*> > SweepLine::getPairs()
{
    if (!m_sorted) {
        sort();
    }
    std::vector<std::pair<LogicObject*, LogicObject*> > returnPairs;
    std::set<Interval> intervals;
    for (const auto& edge : m_objects) {
        Interval objectInterval(edge.index()
                , edge.object()
                , edge.object()->getComponent<Physics>()->rect().yMin()
                , edge.object()->getComponent<Physics>()->rect().yMax());
        // TODO implement an interval tree as an augmented tree
        // Now it uses brute force
        for (const auto& interval : intervals) {
            if (objectInterval.intersect(interval)) {
                returnPairs.push_back(std::pair
                        <LogicObject*, LogicObject*>
                        (objectInterval.object, interval.object));
            }
        }
        if (edge.isBegin()) {
            intervals.insert(objectInterval);
        } else {
            assert(intervals.find(objectInterval) != intervals.end());
            intervals.erase(intervals.find(objectInterval));
        }
    }
    return returnPairs;
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
    EngineUnit pivotValue = m_objects[(left + right) / 2].position();
    while (i <= j) {
        while (m_objects[i].position() < pivotValue) {
            ++i;
        }
        while (m_objects[j].position() > pivotValue) {
            --j;
        }
        if (i <= j) {
            RectangleEdge tmp = m_objects[i];
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
    RectangleEdge key = m_objects.back();
    int i = static_cast<int>(m_objects.size());
    while (i != 0 && m_objects[i - 1].position() > key.position()) {
        m_objects[i] = m_objects[i - 1];
        --i;
    }
    m_objects[i] = key;
}


} // namespace Core
