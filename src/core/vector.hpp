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
    EngineUnit x();
    EngineUnit y();
    void setX(EngineUnit x);
    void setY(EngineUnit y);
    EngineUnit magnitude();
    float angle();
    float angleInRadians();
    Vector& operator+=(Vector& vector);
    Vector& operator*=(float& multiplier);
};

Vector& operator+(Vector& vector1, Vector& vector2);
Vector& operator*(Vector& vector, float& multiplier);
Vector& operator*(float& multiplier, Vector& vector);
} // namespace Core

#endif //_CORE_VECTOR_HPP_
