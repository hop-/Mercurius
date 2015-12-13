#ifndef _MML_MMLATTRIBUTE_HPP
#define _MML_MMLATTRIBUTE_HPP

#include "mml_object.hpp"

namespace MML
{

//template <typename T>
class MMLAttribute : public MMLObject
{
public:
    MMLAttribute(const std::string& n, const std::string& vt/*, const T& v*/)
        : MMLObject(n)
//        , m_value(v)
    {
        setType(vt);
    }

/*public:
    const T& getValue() const
    {
        return m_value;
    }

public:
    void setValue(const T& v)
    {
        m_value = v;
    }

private:
    T m_value;*/
};

} // MML

#endif // _MML_MMLATTRIBUTE_HPP
