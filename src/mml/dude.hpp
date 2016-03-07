#ifndef _MML_DUDE_HPP_
#define _MML_DUDE_HPP_

#include "drawable_object.hpp"

namespace MML
{

class Dude
    : public DrawableObject
{
public:
    class Factory
        : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    Dude(const std::string& n);
};

} // namespace MML

#endif //_MML_DUDE_HPP_
