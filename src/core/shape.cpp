#include "shape.hpp"

namespace Core
{

Shape::Shape(EngineUnit width, EngineUnit height,const Position& position)
    : m_width(width)
    , m_height(height)
    , m_position(position)
{}

Shape::Shape()
    : Shape(0, 0, Position())
{}

} // namespace Core
