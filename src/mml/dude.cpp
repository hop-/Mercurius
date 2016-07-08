#include "dude.hpp"

namespace MML
{

MMLObject* Dude::Factory::
create(const std::string& n)
{
    return new Dude(n);
}

Dude::
Dude(const std::string& n)
    : DrawableObject(n)
{
    setType("dude");
}

} // namespace MML
