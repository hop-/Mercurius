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
~MMLAttribute()
{
    assert(m_private != 0);
    delete m_private;
    m_private = 0;
}

} // MML
