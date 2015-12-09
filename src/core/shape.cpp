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

EngineUnit Shape::width()
{
    return m_width;
}

EngineUnit Shape::height()
{
    return m_height;
}

void Shape::setWidth(EngineUnit width)
{
    m_width = width;
}

void Shape::setHeight(EngineUnit height)
{
    m_height = height;
}

} // namespace Core
