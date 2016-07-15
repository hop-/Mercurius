#ifndef _MML_BEING_HPP_
#define _MML_BEING_HPP_

#include "drawable_object.hpp"

namespace MML
{

class Being
    : public DrawableObject
{
public:
    class Factory : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    Being(const std::string& n);
};

} // namespace MML

#endif //_MML_BEING_HPP_
