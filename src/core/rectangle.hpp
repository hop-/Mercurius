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
    Rectangle represent(const Rectangle& rectangle) const;
    Rectangle scaled(float scale) const;
    bool isInside(const Rectangle& rect) const;
    bool intersects(const Rectangle& rect) const;
    bool contacts(const Rectangle& rect) const;

public:
    EngineUnit right() const;
    EngineUnit left() const;
    EngineUnit top() const;
    EngineUnit bottom() const;

public:
    const EngineUnit& width() const;
    const EngineUnit& height() const;
    const Position& position() const;
    void setWidth(const EngineUnit& width);
    void setHeight(const EngineUnit& height);
    void setPosition(const Position& position);
    void setX(const EngineUnit& x);
    void setY(const EngineUnit& y);
};

} // namespace Core

#endif //_CORE_RECTANGLE_HPP_
