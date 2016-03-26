#include "sweep_line.hpp"

#include "logic_object.hpp"
#include "components.hpp"
#include "game.hpp"
#include "event_manager.hpp"
#include "events.hpp"

#include <set>
#include <cmath>
#include <cassert>
#include <algorithm>

namespace Core
{


// SweepLine::RectangleEdge

int SweepLine::RectangleEdge::m_currentIndex = 0;

SweepLine::RectangleEdge::RectangleEdge(int index
        , const LogicObject* object, EngineUnit position, bool isBegin)
    : m_index(index)
    , m_object(object)
    , m_position(position)
    , m_begin(isBegin)
{}

void SweepLine::RectangleEdge::generate(SweepLine& parent
        , const LogicObject* object)
{
    assert(0 != object);
    assert(0 != object->component<Collider>());
    parent.insert(RectangleEdge(m_currentIndex, object
                , object->component<Collider>()->rect().xMin(), true));
    parent.insert(RectangleEdge(m_currentIndex, object
                , object->component<Collider>()->rect().xMax(), false));
    ++m_currentIndex;
}

// SweepLine::Interval

SweepLine::Interval::Interval(int nIndex, const LogicObject* nObject
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

void SweepLine::insert(const LogicObject* object)
{
    assert(0 != object);
    assert(0 != object->component<Collider>());
    RectangleEdge::generate(*this, object);
}

void SweepLine::insert(const RectangleEdge& object)
{
    m_objects.push_back(object);
    if (m_sorted) {
        sortLastInserted();
    }
}

void SweepLine::update(const LogicObject* object)
{
    // TODO performance improvement
    if (remove(object)) {
        insert(object);
    }
}

bool SweepLine::remove(const LogicObject* object)
{
    // TODO performance improvement
    int count = 0;
    for (RectEdges::iterator it = m_objects.begin()
            ; it != m_objects.end(); ++it) {
        if (it->object() == object) {
            ++count;
            RectEdges::iterator tmpIt = it;
            --it;
            m_objects.erase(tmpIt);
            if (2 == count) {
                return true;
            }
        }
    }
    return false;
}
/*
void SweepLine::run()
{
    LogicObjectPairs pairs = getPairs();
    // TODO performance improvement
    for (const auto& pair : pairs) {
        bool found = false;
        for (LogicObjectPairs::iterator existPair = m_pairs.begin()
               ; existPair != m_pairs.end(); ++existPair) {
            if ((pair.first == existPair->first
                        && pair.second == existPair->second)
                    || (pair.first == existPair->second
                        && pair.second == existPair->first))
            {
                m_pairs.erase(existPair);
                found = true;
                break;
            }
        }
        if (!found) {
            Game::getInstance()->eventManager()
                ->push(new ObjectCollision(
                            pair
                            , ObjectCollision::Status::Collided));
        }
    }
    for (const auto& existPair : m_pairs) {
        Game::getInstance()->eventManager()->push(new ObjectCollision(
                    existPair
                    , ObjectCollision::Status::NotCollided));
    }
    m_pairs = pairs;
}
*/
SweepLine::LogicObjectPairs SweepLine::getPairs()
{
    LogicObjectPairs returnPairs;
    if (m_objects.size() == 0) {
        return returnPairs;
    }
    if (!m_sorted) {
        sort();
    }
    std::set<Interval> intervals;
    for (const auto& edge : m_objects) {
        assert(0 != edge.object());
        assert(0 != edge.object()->component<Collider>());
        Interval objectInterval(edge.index()
                , edge.object()
                , edge.object()->component<Collider>()->rect().yMin()
                , edge.object()->component<Collider>()->rect().yMax());
        // TODO implement an interval tree as an augmented tree
        // Now it uses brute force
        if (edge.isBegin()) {
            for (const auto& interval : intervals) {
                if (objectInterval.intersect(interval)) {
                    returnPairs.push_back(LogicObjectPair
                            (objectInterval.object, interval.object));
                }
            }
            intervals.insert(objectInterval);
        } else {
            assert(intervals.find(objectInterval) != intervals.end());
            intervals.erase(objectInterval);
        }
    }
    return returnPairs;
}

void SweepLine::sort()
{
    //quickSort(0, m_objects.size());
    std::sort(m_objects.begin(), m_objects.end()
            , [](const RectangleEdge& a, const RectangleEdge& b) -> bool
            {
                return a.position() < b.position();
            });
    m_sorted = true;
}

// the dunction have no any use.
void SweepLine::quickSort(int left, int right)
{
    int i = left;
    int j = right;
    assert(i != j);
    assert(int(m_objects.size()) > (left + right) / 2);
    assert(0 <= (left + right) / 2);
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
    int i = static_cast<int>(m_objects.size()) - 1;
    while (i != 0 && m_objects[i - 1].position() > key.position()) {
        m_objects[i] = m_objects[i - 1];
        --i;
    }
    m_objects[i] = key;
}


} // namespace Core
