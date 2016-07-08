#include "switch.hpp"

namespace MML
{

MMLObject* Switch::Factory::
create(const std::string& n)
{
    return new Switch(n);
}

Switch::
Switch(const std::string& n)
    : DrawableObject(n)
{
    setType("switch");
}

} // namespace MML
