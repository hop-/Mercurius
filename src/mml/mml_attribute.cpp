#include "mml_attribute.hpp"

namespace MML
{
MMLAttribute::
MMLAttribute(const std::string& n, const std::string& v)
    : MMLObject(n)
{
    setType("attribute");
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
MMLAttribute(const std::string& n, int v)
    : MMLObject(n)
{
    setType("attribute");
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
MMLAttribute(const std::string& n, double v)
    : MMLObject(n)
{
    setType("attribute");
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
MMLAttribute(const std::string& n, bool v)
    : MMLObject(n)
{
    setType("attribute");
    m_private = new MMLAttributePrivate(v, this);
}

MMLAttribute::
~MMLAttribute()
{
    assert(0 != m_private);
    delete m_private;
    m_private = 0;
}

unsigned MMLAttribute::
getType() const
{
    assert(0 != m_private);
    return m_private->getType();
}

} // MML
