#ifndef _MML_DOOR_HPP_
#define _MML_DOOR_HPP_

#include "drawable_object.hpp"

#include <string>

namespace MML
{

class Door
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
    Door(const std::string& n);
};

} // namespace MML

#endif //_MML_DOOR_HPP_
