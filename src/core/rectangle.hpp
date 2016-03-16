#ifndef _CORE_RECTANGLE_HPP_
#define _CORE_RECTANGLE_HPP_

#include "units.hpp"
#include "position.hpp"

namespace Core
{

class Rectangle
{
    EngineUnit m_width;
    EngineUnit m_height;
    Position m_position;

public:
    Rectangle(EngineUnit width, EngineUnit height,const Position& position);
    Rectangle();
    virtual ~Rectangle() = default;

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

    inline void setX(const EngineUnit& x)
    {
        m_position.setX(x);
    }

    inline void setY(const EngineUnit& y)
    {
        m_position.setY(y);
    }

    Rectangle represent(const Rectangle& rectangle) const;
    Rectangle scaled(float scale);
    bool isInside(const Rectangle& rect) const;

    EngineUnit xMax() const;
    EngineUnit xMin() const;
    EngineUnit yMax() const;
    EngineUnit yMin() const;
};

} // namespace Core

#endif //_CORE_RECTANGLE_HPP_
