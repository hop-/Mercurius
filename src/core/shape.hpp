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
    virtual ~Shape() = default;

public:
    inline const EngineUnit& width() const
    {
        return m_width;
    }

    inline const EngineUnit& height() const
    {
        return m_height;
    }

    inline void setWidth(const EngineUnit& width)
    {
        m_width = width;
    }

    inline void setHeight(const EngineUnit& height)
    {
        m_height = height;
    }
};

} // namespace Core

#endif //_CORE_SHAPE_HPP_
