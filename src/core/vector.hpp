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
    const EngineUnit& x() const;
    const EngineUnit& y() const;
    void setX(EngineUnit x);
    void setY(EngineUnit y);
    EngineUnit magnitude() const;
    float angle() const;
    float angleInRadians() const;
    void setAngle(float angle);
    bool isMoving(Direction d) const;

public:
    Vector& operator+=(const Vector& vector);
    Vector& operator*=(const float& multiplier);
};

Vector operator+(const Vector& vector1, const Vector& vector2);
Vector operator*(const Vector& vector, const float& multiplier);
Vector operator*(const float& multiplier, const Vector& vector);
} // namespace Core

#endif //_CORE_VECTOR_HPP_
