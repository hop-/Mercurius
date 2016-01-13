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
    std::vector<std::pair<LogicObject*, Rectangle> > m_objects; 
    bool m_sorted;

public:
    SweepLine();
    ~SweepLine();

public:
    void insert(LogicObject* object);

private:
    void sort();
    void quickSort(int left, int right);
    void sortLastInserted();
};

} // namespace Core

#endif //_CORE_SWEEP_LINE_HPP_
