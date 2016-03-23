#include "ground.hpp"

namespace MML
{

MMLObject* Ground::Factory::create(const std::string& n)
{
    return new Ground(n);
}

Ground::Ground(const std::string& n)
    : DrawableObject(n)
{
    setType("ground");
}

} // namespace MML
