#ifndef _MML_PLATFORM_HPP_
#define _MML_PLATFORM_HPP_

#include "drawable_object.hpp"

#include <string>

namespace MML
{

class Platform
    : public DrawableObject
{
public:
    class Factory
        : public MMLObject::AbstractFactory
    {
    public:
        MMLObject* create(const std::string& n) override;
    };

public:
    Platform(const std::string& n);
};

} // namespace MML

#endif //_MML_PLATFORM_HPP_
