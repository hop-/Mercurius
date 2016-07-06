#ifndef _CORE_POSITION_HPP_
#define _CORE_POSITION_HPP_

#include "units.hpp"
#include "vector.hpp"

namespace Core
{

class Position
{
    EngineUnit m_x;
    EngineUnit m_y;

public:
    Position(EngineUnit x, EngineUnit y);
    Position();

public:
    const EngineUnit& x() const;
    const EngineUnit& y() const;
    void setX(const EngineUnit& x);
    void setY(const EngineUnit& y);

public:
    Position operator-(const Position& p) const;
    Position operator+(const Position& p) const;
    Position operator*(float f) const;
    void move(Vector vector);
};

} // namespace Core

#endif //_CORE_POSITION_HPP_
