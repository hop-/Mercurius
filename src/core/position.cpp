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

Position Position::operator-(const Position& p) const
{
    Position returnPosition;
    returnPosition.setX(m_x - p.x());
    returnPosition.setY(m_y - p.y());
    return returnPosition;
}

Position Position::operator+(const Position& p) const
{
    Position returnPosition;
    returnPosition.setX(m_x + p.x());
    returnPosition.setY(m_y + p.y());
    return returnPosition;
}

Position Position::operator*(float f) const
{
    Position returnPosition;
    returnPosition.setX(m_x * f);
    returnPosition.setY(m_y * f);
    return returnPosition;
}

void Position::move(Vector vector)
{
    m_x += vector.x();
    m_y += vector.y();
}

} // namespace Core
