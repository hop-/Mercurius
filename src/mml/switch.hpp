#ifndef _MML_SWITCH_HPP_
#define _MML_SWITCH_HPP_

#include "drawable_object.hpp"

#include <string>

namespace MML
{

class Switch
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
    Switch(const std::string& n);
};

} // namespace MML

#endif //_MML_SWITCH_HPP_
