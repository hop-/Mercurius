#ifndef _CORE_VECTOR_HPP_
#define _CORE_VECTOR_HPP_

#include "units.hpp"

namespace Core
{

class Vector
{
    EngineUnit m_x;
    EngineUnit m_y;

public:
    Vector();
    Vector(EngineUnit magnitude, float angle);

public:
    inline const EngineUnit& x() const
    {
        return m_x;
    }

    inline const EngineUnit& y() const
    {
        return m_y;
    }

    inline void setX(EngineUnit x)
    {
        m_x = x;
    }

    inline void setY(EngineUnit y)
    {
        m_y = y;
    }

    EngineUnit magnitude() const;
    float angle() const;
    float angleInRadians() const;
    void setAngle(float angle);

    Vector& operator+=(const Vector& vector);
    Vector& operator*=(const float& multiplier);
};

Vector& operator+(const Vector& vector1, const Vector& vector2);
Vector& operator*(const Vector& vector, const float& multiplier);
Vector& operator*(const float& multiplier, const Vector& vector);
} // namespace Core

#endif //_CORE_VECTOR_HPP_
