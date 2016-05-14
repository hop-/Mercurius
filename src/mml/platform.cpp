#include "platform.hpp"

namespace MML
{

MMLObject* Platform::Factory::create(const std::string& n)
{
    return new Platform(n);
}

Platform::Platform(const std::string& n)
    : DrawableObject(n)
{
    setType("platform");
}

} // namespace MML
