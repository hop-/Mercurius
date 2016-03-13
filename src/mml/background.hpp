#ifndef _MML_BACKGROUND_HPP_
#define _MML_BACKGROUND_HPP_

#include "drawable_object.hpp"

namespace MML
{

class Background
    : public DrawableObject
{
public:
    class BackgroundFactory : public MMLObject::AbstractFactory
    {
    public:
        virtual MMLObject* create(const std::string& n);
    };

public:
    Background(const std::string& n);
};

} // namespace MML

#endif // _MML_BACKGROUND_HPP_
