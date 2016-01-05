#include "shape.hpp"

namespace Core
{

Shape::Shape(EngineUnit width, EngineUnit height)
    : m_width(width)
    , m_height(height)
{}

Shape::Shape()
    : Shape(0, 0)
{}

} // namespace Core
