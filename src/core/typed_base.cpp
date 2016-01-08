#include "typed_base.hpp"

namespace Core
{

int TypedBase::ID::m_count = 0;

TypedBase::ID::ID()
    : m_id(++m_count)
{}

TypedBase::ID::operator int() const
{
    return m_id; 
}

bool TypedBase::Less::operator()(TypedBase* left, TypedBase* right) const
{
    assert(0 != left);
    assert(0 != right);
    if (left->getType() == right->getType()) {
        return left->less(right);
    }
    return left->getType() < right->getType();
}

} // namespace Core
