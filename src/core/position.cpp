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

void Position::move(Vector vector)
{
    m_x += vector.x();
    m_y += vector.y();
}

} // namespace Core
