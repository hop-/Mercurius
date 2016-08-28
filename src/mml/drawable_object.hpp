#ifndef _MML_DRAWABLE_OBJECT_HPP_
#define _MML_DRAWABLE_OBJECT_HPP_

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
    ATTRIBUTE_INTERFACE(MMLAttribute::Pair, "body", body);
    ATTRIBUTE_INTERFACE(MMLAttribute::Pair, "offset", offset)
    ATTRIBUTE_INTERFACE(double, "weight", weight);
    ATTRIBUTE_INTERFACE(double, "width", width);
    ATTRIBUTE_INTERFACE(double, "height", height);
    ATTRIBUTE_INTERFACE(double, "scale", scale);
    ATTRIBUTE_INTERFACE(int, "priority", priority);
    ATTRIBUTE_INTERFACE(bool, "aimed", aimed); // TODO TMP
    ATTRIBUTE_INTERFACE(std::string, "texture", texture);
    ATTRIBUTE_INTERFACE(MMLAttribute::StringList
            , "animationList", animationList);
};

} // namespae MML

#endif // _MML_DRAWABLE_OBJECT_HPP_
