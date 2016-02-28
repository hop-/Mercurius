#ifndef _MML_MMLBOX_HPP
#define _MML_MMLBOX_HPP

#include "macros.hpp"
#include "mml_object.hpp"

namespace MML
{

class MMLBox
    : public MMLObject
{
public:
    class BoxFactory : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    ATTRIBUTE_INTERFACE(int, "width", width);
    ATTRIBUTE_INTERFACE(int, "height", height);

public:
    MMLBox(const std::string& n);
};

} // namespace MML

#endif // _MML_MMLBOX_HPP
