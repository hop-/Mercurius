#include "mml_box.hpp"
#include "mml_attribute.hpp"

namespace MML
{

MMLObject* MMLBox::BoxFactory::
create(const std::string& n)
{
    return new MMLBox(n);
}

MMLBox::
MMLBox(const std::string& n)
    : DrawableObject(n)
{
    setType("box");
}

} // MML
