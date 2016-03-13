#include "background.hpp"
#include "mml_attribute.hpp"

namespace MML
{

MMLObject* Background::BackgroundFactory::
create(const std::string& n)
{
    return new Background(n);
}

Background::
Background(const std::string& n)
    : DrawableObject(n)
{
    setType("background");
}

} // MML
