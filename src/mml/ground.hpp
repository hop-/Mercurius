#ifndef _MML_GROUND_HPP_
#define _MML_GROUND_HPP_

#include "drawable_object.hpp"

namespace MML
{

class Ground
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
    Ground(const std::string& n);
};

} // namespace MML

#endif //_MML_GROUND_HPP_
