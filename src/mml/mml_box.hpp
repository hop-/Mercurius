#ifndef _MML_MMLBOX_HPP
#define _MML_MMLBOX_HPP

#include "drawable_object.hpp"

namespace MML
{

class MMLBox
    : public DrawableObject
{
public:
    class BoxFactory : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    MMLBox(const std::string& n);
};

} // namespace MML

#endif // _MML_MMLBOX_HPP
