#include "event.hpp"

namespace Core
{

int Event::ID::m_count = 0;

Event::ID::ID() :
    m_id(++m_count)
{}

Event::ID::operator int() const
{
    return m_id; 
}

} // namespace Core
