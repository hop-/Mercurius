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
    : m_x(magnitude* std::cos(angle *_PI / 180))
    , m_y(magnitude* std::sin(angle *_PI / 180))
{}

EngineUnit Vector::x()
{
    return m_x;
}

EngineUnit Vector::y()
{
    return m_y;
}

void Vector::setX(EngineUnit x)
{
    m_x = x;
}

void Vector::setY(EngineUnit y)
{
    m_y = y;
}

EngineUnit Vector::magnitude()
{
    return std::sqrt(m_x*m_x + m_y*m_y);
}

float Vector::angle()
{
    return angleInRadians() * 180 / _PI;
}

float Vector::angleInRadians()
{
    return std::atan2(m_y, m_x);
}

Vector& Vector::operator+=(Vector& vector)
{
    m_x += vector.x();
    m_y += vector.y();
    return *this;
}

Vector& Vector::operator*=(float& multiplier)
{
    m_x *= multiplier;
    m_y *= multiplier;
    return *this;
}

Vector& operator+(Vector& vector1, Vector& vector2)
{
    Vector v = vector1;
    return v += vector2;
}

Vector& operator*(float& multiplier, Vector& vector)
{
    Vector v = vector;
    return v *= multiplier;
}

Vector& operator*(Vector& vector, float& multiplier)
{
    Vector v = vector;
    return v *= multiplier;
}

} // namespace Core
