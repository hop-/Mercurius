#ifndef _CORE_SWEEP_LINE_HPP_
#define _CORE_SWEEP_LINE_HPP_

#include "units.hpp"
#include "rectangle.hpp"

#include <vector>

namespace Core
{

class LogicObject;

class SweepLine
{
public:
    using LogicObjectPair = std::pair<const LogicObject*
        , const LogicObject*>;
    using LogicObjectPairVector = std::vector<LogicObjectPair>;

private:
    class RectangleEdge
    {
        static int m_currentIndex;
        int m_index;
        const LogicObject* m_object;
        EngineUnit m_position;
        bool m_begin;

    public:
        static void generate(SweepLine& parent, const LogicObject* object);

        inline int index() const
        {
            return m_index;
        }

        inline const LogicObject* object() const
        {
            return m_object;
        }

        inline EngineUnit position() const
        {
            return m_position;
        }

        inline bool isBegin() const
        {
            return m_begin;
        }

        inline bool isEnd() const
        {
            return !isBegin();
        }

    private:
        RectangleEdge(int index, const LogicObject* object
                , EngineUnit position, bool isBegin);
    };

private:
    struct Interval
    {
        const int index;
        const LogicObject* const object;
        const EngineUnit min;
        const EngineUnit max;

        Interval(int nIndex, const LogicObject* nObject
                , EngineUnit nMin, EngineUnit nMax);
        bool intersect(const Interval& interval) const;

        inline bool operator==(const Interval& cmp) const
        {
            return index == cmp.index;
        }

        inline bool operator<(const Interval& cmp) const
        {
            return min < cmp.min;
        }
    };

private:
    std::vector<RectangleEdge> m_objects;
    bool m_sorted;

public:
    SweepLine();
    ~SweepLine();

public:
    void insert(const LogicObject* object);
    LogicObjectPairVector getPairs();

private:
    void insert(const RectangleEdge& object);
    void sort();
    void quickSort(int left, int right);
    void sortLastInserted();
};

} // namespace Core

#endif //_CORE_SWEEP_LINE_HPP_
