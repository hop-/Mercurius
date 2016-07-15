#include "being.hpp"

namespace MML
{

MMLObject* Being::Factory::
create(const std::string& n)
{
    return new Being(n);
}

Being::
Being(const std::string& n)
    : DrawableObject(n)
{
    setType("being");
}

} // namespace MML
