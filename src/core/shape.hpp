#ifndef _CORE_SHAPE_HPP_
#define _CORE_SHAPE_HPP_

#include "units.hpp"

namespace Core
{

class Shape
{
    EngineUnit m_width;
    EngineUnit m_height;

public:
    Shape(EngineUnit width, EngineUnit height);
    Shape();

public:
    EngineUnit width();
    EngineUnit height();
    void setWidth(EngineUnit width);
    void setHeight(EngineUnit height);
};

} // namespace Core

#endif //_CORE_SHAPE_HPP_
