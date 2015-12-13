#include "mml_object.hpp"

namespace MML
{

MMLObject::CMMLAttributes& MMLObject::
getAttributes() const
{
    return m_attributes;
}

void MMLObject::addAttribute(MMLAttribute* a)
{
    Q_ASSERT(0 != a);
    m_attributes.push_back(a);
}

} // namespace MML
