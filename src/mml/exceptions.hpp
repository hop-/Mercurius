#ifndef _MML_EXCEPTIONS_HPP_
#define _MML_EXCEPTIONS_HPP_

#include <base/exception.hpp>

namespace MML {

class MMLSyntaxError
   : public Base::Exception
{
public:
    virtual const std::string what() const
    {
        return "MML sytaxs error, please check mml file.";
    }
};

class MMLNoAttribute
    : public Base::Exception
{
public:
    MMLNoAttribute(const std::string& type_name, const std::string& attr_name)
        : m_type_name(type_name)
        , m_attr_name(attr_name)
    {}

public:
    virtual const std::string what() const
    {
        return "Attribute with name " + m_attr_name + " doesn't exists for MML type "
               + m_type_name;
    }

private:
    std::string m_type_name;
    std::string m_attr_name;
};

class MMLNameExists
    : public Base::Exception
{
public:
    MMLNameExists(const std::string& name)
        : m_name(name)
    {}

public:
    virtual const std::string what() const
    {
        return "Object with name " + m_name + " already exists.";
    }

private:
    std::string m_name;
};

} // namespace MML

#endif // _MML_EXCEPTIONS_HPP_
