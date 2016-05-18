#include "typed_base.hpp"

namespace Base
{

int TypedBase::ID::m_count = 0;

TypedBase::ID::ID()
    : m_id(++m_count)
{}

TypedBase::ID::operator int() const
{
    return m_id;
}

} // namespace Base
