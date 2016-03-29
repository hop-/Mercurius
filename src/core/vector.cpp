#include "vector.hpp"

#include <cmath>

#ifdef M_PI
    #define _PI M_PI
#else
    #define _PI 3.14159265358979323846
#endif

namespace Core
{

Vector::Vector()
    : m_x(0)
    , m_y(0)
{}

Vector::Vector(EngineUnit magnitude, float angle)
    : m_x(magnitude * std::cos(angle *_PI / 180))
    , m_y(magnitude * std::sin(angle *_PI / 180))
{}

EngineUnit Vector::magnitude() const
{
    return std::sqrt(m_x*m_x + m_y*m_y);
}

float Vector::angle() const
{
    return angleInRadians() * 180 / _PI;
}

float Vector::angleInRadians() const
{
    return std::atan2(engineUnit(m_y), engineUnit(m_x));
}

void Vector::setAngle(float angle)
{
    EngineUnit m = magnitude();
    m_x = m * std::cos(angle *_PI / 180);
    m_y = m * std::sin(angle *_PI / 180);
}

Vector& Vector::operator+=(const Vector& vector)
{
    m_x += vector.x();
    m_y += vector.y();
    return *this;
}

Vector& Vector::operator*=(const float& multiplier)
{
    m_x *= multiplier;
    m_y *= multiplier;
    return *this;
}

Vector operator+(const Vector& vector1, const Vector& vector2)
{
    Vector v = vector1;
    return v += vector2;
}

Vector operator*(const float& multiplier, const Vector& vector)
{
    Vector v = vector;
    return v *= multiplier;
}

Vector operator*(const Vector& vector, const float& multiplier)
{
    Vector v = vector;
    return v *= multiplier;
}

} // namespace Core
