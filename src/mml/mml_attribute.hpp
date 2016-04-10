#ifndef _MML_MMLATTRIBUTE_HPP
#define _MML_MMLATTRIBUTE_HPP

#include "mml_object.hpp"
#include "mml_attribute_p.hpp"

#include <core/frame.hpp>

#include <cassert>

namespace MML
{

class MMLAttribute
{
    std::string m_name = "";
    MMLAttributePrivate* m_private = 0;

public:
    typedef std::pair<int, int> IntPair;
    typedef Core::Frame::ScreenMode ScreenMode;

public:
    MMLAttribute(const MMLAttribute&);
    MMLAttribute(const std::string& n, const std::string& v);
    MMLAttribute(const std::string& n, int v);
    MMLAttribute(const std::string& n, double v);
    MMLAttribute(const std::string& n, bool v);
    MMLAttribute(const std::string& n, IntPair);
    MMLAttribute(const std::string& n, ScreenMode v);
    virtual ~MMLAttribute();

    MMLAttribute& operator=(const MMLAttribute&);

public:
    const std::string& getName() const;

public:
    unsigned getType() const;

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
