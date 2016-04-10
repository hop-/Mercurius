#ifndef _MML_CONFIG_HPP_
#define _MML_CONFIG_HPP_

#include "macros.hpp"
#include "mml_attribute.hpp"
#include "mml_object.hpp"

namespace MML {

class Config : public MMLObject
{
public:
    class Factory
        : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    Config(const std::string& name);

public:
    ATTRIBUTE_INTERFACE(MMLAttribute::IntPair, "resolution", resolution);
    ATTRIBUTE_INTERFACE(MMLAttribute::ScreenMode, "screenMode", screenMode);
    ATTRIBUTE_INTERFACE(bool, "default", isDefault);

};

} // namespace MML

#endif // _MML_CONFIG_HPP_
