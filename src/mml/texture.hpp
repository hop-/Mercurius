#ifndef _MML_TEXTURE_HPP_
#define _MML_TEXTURE_HPP_

#include "macros.hpp"
#include "mml_attribute.hpp"
#include "mml_object.hpp"

namespace MML {

class Texture : public MMLObject
{
public:
    class Factory
        : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    Texture(const std::string& name);

public:
    ATTRIBUTE_INTERFACE(MMLAttribute::IntPair, "size", size);
    ATTRIBUTE_INTERFACE(MMLAttribute::IntPair, "frameSize", frameSize);
    ATTRIBUTE_INTERFACE(std::string, "path", path);
};

} // namespace MML

#endif // _MML_TEXTURE_HPP_
