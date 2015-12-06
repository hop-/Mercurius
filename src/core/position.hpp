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
    EngineUnit x();
    EngineUnit y();
    void setX(EngineUnit x);
    void setY(EngineUnit y);
    void move(Vector vector);
};

} // namespace Core

#endif //_CORE_POSITION_HPP_
