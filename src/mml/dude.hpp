#ifndef _MML_DUDE_HPP_
#define _MML_DUDE_HPP_

#include "macros.hpp"
#include "mml_attribute.hpp"
#include "mml_object.hpp"

namespace MML
{

class Dude
    : public MMLObject
{
public:
    class Factory
        : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    ATTRIBUTE_INTERFACE(MMLAttribute::IntPair, "position", position);
    ATTRIBUTE_INTERFACE(int, "width", width);
    ATTRIBUTE_INTERFACE(int, "height", height);
    ATTRIBUTE_INTERFACE(std::string, "texture", texture);

public:
    Dude(const std::string& n);
};

} // namespace MML

#endif //_MML_DUDE_HPP_
