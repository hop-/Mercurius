#ifndef _MML_MMLATTRIBUTE_HPP
#define _MML_MMLATTRIBUTE_HPP

#include "mml_object.hpp"
#include "mml_attribute_p.hpp"
#include <cassert>

namespace MML
{

class MMLAttribute : public MMLObject
{
    MMLAttributePrivate* m_private;

public:
    MMLAttribute(const std::string& n, const std::string& v);
    MMLAttribute(const std::string& n, int v);
    MMLAttribute(const std::string& n, double v);
    MMLAttribute(const std::string& n, bool v);
    virtual ~MMLAttribute();

public:
    template <typename T>
    T getValue() const
    {
        assert(m_private != 0);
        return m_private->getValue();
    }

    template <typename T>
    void setValue(const T& v)
    {
        assert(m_private != 0);
        m_private->setValue(v);
    }
};

} // MML

#endif // _MML_MMLATTRIBUTE_HPP
