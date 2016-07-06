#include "units.hpp"

namespace Core
{

namespace {const int precision = 1000;}

EngineUnit::
EngineUnit()
    : m_value(0)
{}

EngineUnit::
EngineUnit(engineUnit value)
    : m_value(value)
{}

EngineUnit::
operator engineUnit() const
{
    return m_value;
}

EngineUnit::
operator UserUnit() const
{
    return UserUnit(userUnit(m_value) / precision);
}

EngineUnit EngineUnit::
operator+=(EngineUnit e)
{
    return m_value += e;
}

EngineUnit EngineUnit::
operator*=(EngineUnit e)
{
    return m_value *= e;
}

UserUnit::
UserUnit()
    : m_value(0)
{}

UserUnit::
UserUnit(userUnit value)
    : m_value(value)
{}

UserUnit::
operator userUnit() const
{
    return m_value;
}

UserUnit::
operator EngineUnit() const
{
    return EngineUnit(userUnit(m_value) * precision);
}

UserUnit UserUnit::
operator+=(UserUnit u)
{
    return m_value += u;
}

UserUnit UserUnit::
operator*=(UserUnit u)
{
    return m_value *= u;
}

} // namespace Core
