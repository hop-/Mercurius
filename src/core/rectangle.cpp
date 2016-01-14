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

EngineUnit Rectangle::xMax()
{
    if (m_width > 0) {
        return m_position.x() + m_width;
    } else {
        return m_position.x();
    }
}

EngineUnit Rectangle::xMin()
{
    if (m_width > 0) {
        return m_position.x();
    } else {
        return m_position.x() + m_width;
    }
}

EngineUnit Rectangle::yMax()
{
    if (m_height > 0) {
        return m_position.y() + m_height;
    } else {
        return m_position.y();
    }
}

EngineUnit Rectangle::yMin()
{
    if (m_height > 0) {
        return m_position.y();
    } else {
        return m_position.y() + m_height;
    }
}


} // namespace Core
