#ifndef _MML_STAIRS_HPP_
#define _MML_STAIRS_HPP_

#include "drawable_object.hpp"

namespace MML
{

class Stairs
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
    Stairs(const std::string& n);
};

} // namespace MML

#endif //_MML_STAIRS_HPP_
