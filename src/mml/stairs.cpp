#include "stairs.hpp"

namespace MML
{

MMLObject* Stairs::Factory::create(const std::string& n)
{
    return new Stairs(n);
}

Stairs::Stairs(const std::string& n)
    : DrawableObject(n)
{
    setType("stairs");
}

} // namespace MML
