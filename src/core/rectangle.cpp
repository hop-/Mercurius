#include "rectangle.hpp"

namespace Core
{


Rectangle::Rectangle(EngineUnit width, EngineUnit height,const Position& position)
    : m_width(width)
    , m_height(height)
    , m_position(position)
{}

Rectangle::Rectangle()
    : Rectangle(0, 0, Position())
{}

Rectangle Rectangle::represent(const Rectangle& rectangle) const
{
    Rectangle rect = rectangle;
    rect.setPosition(rectangle.position() - m_position);
    return rect;
}

bool Rectangle::isInside(const Rectangle& rect) const
{
    return (right() >= rect.right()
            && left() <= rect.left()
            && top() >= rect.top()
            && bottom() <= rect.bottom());
}

Rectangle Rectangle::scaled(float scale)
{
    Rectangle rectangle;
    rectangle.setWidth(m_width * scale);
    rectangle.setHeight(m_height * scale);
    rectangle.setPosition(m_position * scale);
    return rectangle;
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    return (left() < rect.right()
            && right() > rect.left()
            && bottom() < rect.top()
            && top() > rect.bottom());
}

EngineUnit Rectangle::right() const
{
    if (m_width > 0) {
        return m_position.x() + m_width;
    } else {
        return m_position.x();
    }
}

EngineUnit Rectangle::left() const
{
    if (m_width > 0) {
        return m_position.x();
    } else {
        return m_position.x() + m_width;
    }
}

EngineUnit Rectangle::top() const
{
    if (m_height > 0) {
        return m_position.y() + m_height;
    } else {
        return m_position.y();
    }
}

EngineUnit Rectangle::bottom() const
{
    if (m_height > 0) {
        return m_position.y();
    } else {
        return m_position.y() + m_height;
    }
}


} // namespace Core
