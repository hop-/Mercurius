#include "mml_object.hpp"
#include "mml_attribute.hpp"

#include <cassert>

namespace MML
{

MMLObject::
MMLObject(const std::string& n, MMLObject* p)
    : m_name(n)
    , m_parent(p)
{
    assert(!n.empty());
}

MMLObject::
~MMLObject()
{}

const std::string& MMLObject::
getName() const
{
    return m_name;
}

MMLObject::CMMLAttributes& MMLObject::
getAttributes() const
{
    return m_attributes;
}

void MMLObject::
addAttribute(MMLAttribute* a)
{
    assert(0 != a);
    a->setParent(this);
    m_attributes.push_back(a);
}

const std::string& MMLObject::
getType()
{
    return m_type;
}

void MMLObject::
setType(const std::string& type)
{
    assert(!type.empty());
    m_type = type;
}

void MMLObject::
setParent(MMLObject* p)
{
    m_parent = p;
}

const MMLObject* MMLObject::
getParent() const
{
    return m_parent;
}

} // namespace MML
