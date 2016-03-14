#ifndef _MML_DRAWABLE_OBJECT_HPP
#define _MML_DRAWABLE_OBJECT_HPP

#include "macros.hpp"
#include "mml_attribute.hpp"
#include "mml_object.hpp"

namespace MML {

class DrawableObject
    : public MMLObject
{
public:
    DrawableObject(const std::string& name);

public:
    ATTRIBUTE_INTERFACE(MMLAttribute::IntPair, "position", position);
    ATTRIBUTE_INTERFACE(int, "weight", weight);
    ATTRIBUTE_INTERFACE(int, "width", width);
    ATTRIBUTE_INTERFACE(int, "height", height);
    ATTRIBUTE_INTERFACE(double, "scale", scale);
    ATTRIBUTE_INTERFACE(int, "priority", priority);
    ATTRIBUTE_INTERFACE(std::string, "texture", texture);
};

} // namespae MML

#endif // _MML_DRAWABLE_OBJECT_HPP
