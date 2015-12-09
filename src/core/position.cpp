#include "position.hpp"

namespace Core
{

Position::Position(EngineUnit x, EngineUnit y)
    : m_x(x)
    , m_y(y)
{}

Position::Position()
    : Position(0, 0)
{}

EngineUnit Position::x()
{
    return m_x;
}

EngineUnit Position::y()
{
    return m_y;
}

void Position::setX(EngineUnit x)
{
    m_x = x;
}

void Position::setY(EngineUnit y)
{
    m_y = y;
}

void Position::move(Vector vector)
{
    m_x += vector.x();
    m_y += vector.y();
}

} // namespace Core
