#ifndef _MML_ANIMATION_HPP_
#define _MML_ANIMATION_HPP_

#include "macros.hpp"
#include "mml_attribute.hpp"
#include "mml_object.hpp"

namespace MML {

class Animation : public MMLObject
{
public:
    class Factory
        : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    Animation(const std::string& name);

public:
    ATTRIBUTE_INTERFACE(MMLAttribute::IntPair, "position", position);
    ATTRIBUTE_INTERFACE(int, "frameCount", frameCount);
    ATTRIBUTE_INTERFACE(bool, "loop", loop);
    ATTRIBUTE_INTERFACE(int, "fps", fps);
};

} // namespace MML

#endif // _MML_ANIMATION_HPP_
