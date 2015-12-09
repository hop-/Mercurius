#include "logic_object.hpp"

namespace Core
{

void LogicObject::setShape(Shape shape)
{
    m_shape = shape;
}

void LogicObject::setPosition(Position position)
{
    m_position = position;
}

Shape LogicObject::shape()
{
    return m_shape;
}

Position LogicObject::position()
{
    return position;
}

} // namespace Core
