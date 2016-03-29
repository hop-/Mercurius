#include "mml_attribute.hpp"

namespace MML
{
MMLAttribute::
MMLAttribute(const std::string& n, const std::string& v)
    : m_name(n)
{
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
MMLAttribute(const std::string& n, int v)
    : m_name(n)
{
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
MMLAttribute(const std::string& n, double v)
    : m_name(n)
{
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
MMLAttribute(const std::string& n, bool v)
    : m_name(n)
{
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
MMLAttribute(const std::string& n, MMLAttribute::IntPair v)
    : m_name(n)
{
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
~MMLAttribute()
{
    assert(0 != m_private);
    delete m_private;
    m_private = 0;
}

MMLAttribute::
MMLAttribute(const MMLAttribute& a)
{
    m_private = new MMLAttributePrivate(a.m_private, this);
}

MMLAttribute& MMLAttribute::
operator=(const MMLAttribute& a)
{
    if (this != &a) {
        m_private = new MMLAttributePrivate(a.m_private, this);
    }
    return *this;
}

const std::string& MMLAttribute::
getName() const
{
    return m_name;
}

unsigned MMLAttribute::
getType() const
{
    assert(0 != m_private);
    return m_private->getType();
}

} // MML
