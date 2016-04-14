#ifndef _MML_LADDER_HPP_
#define _MML_LADDER_HPP_

#include "drawable_object.hpp"

namespace MML
{

class Ladder
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
    Ladder(const std::string& n);
};

} // namespace MML

#endif //_MML_LADDER_HPP_
