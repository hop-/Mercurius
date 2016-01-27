#ifndef _MML_MMLBOX_HPP
#define _MML_MMLBOX_HPP

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
    MMLBox(const std::string& n);
};

} // namespace MML

#endif // _MML_MMLBOX_HPP
