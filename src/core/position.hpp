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
    inline const EngineUnit& x() const
    {
        return m_x;
    }

    inline const EngineUnit& y() const
    {
        return m_y;
    }

    inline void setX(const EngineUnit& x)
    {
        m_x = x;
    }

    inline void setY(const EngineUnit& y)
    {
        m_y = y;
    }

    void move(Vector vector);
};

} // namespace Core

#endif //_CORE_POSITION_HPP_
