#ifndef _CORE_SHAPE_HPP_
#define _CORE_SHAPE_HPP_

#include "units.hpp"
#include "position.hpp"

namespace Core
{

class Shape
{
    EngineUnit m_width;
    EngineUnit m_height;
    Position m_position;

public:
    Shape(EngineUnit width, EngineUnit height,const Position& position);
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

    inline const Position& position() const
    {
        return m_position;
    }

    inline void setWidth(const EngineUnit& width)
    {
        m_width = width;
    }

    inline void setHeight(const EngineUnit& height)
    {
        m_height = height;
    }

    inline void setPosition(const Position& position)
    {
        m_position = position;
    }
};

} // namespace Core

#endif //_CORE_SHAPE_HPP_
