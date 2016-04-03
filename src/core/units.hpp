#ifndef _CORE_UNITS_HPP_
#define _CORE_UNITS_HPP_

namespace Core
{

#define PRECISION 1000

using engineUnit = long long int;
using userUnit = float;

class UserUnit;

class EngineUnit
{
    engineUnit m_value;

public:
    EngineUnit();
    EngineUnit(engineUnit value);
    operator engineUnit() const;
    operator UserUnit() const;
    EngineUnit operator+=(EngineUnit e);
    EngineUnit operator*=(EngineUnit e);
};

class UserUnit
{
    userUnit m_value;

public:
    UserUnit();
    UserUnit(userUnit value);
    operator userUnit() const;
    operator EngineUnit() const;
    UserUnit operator+=(UserUnit u);
    UserUnit operator*=(UserUnit u);
};

enum class Direction {
    Left = 0
    , Right
    , Up
    , Down
    , None
};

enum class HorizontalDirection {
    Left = 0
    , Right
};

} // namespace Core

#endif //_CORE_UNITS_HPP_
