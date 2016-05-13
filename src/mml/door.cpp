#include "door.hpp"

namespace MML
{

MMLObject* Door::Factory::create(const std::string& n)
{
    return new Door(n);
}

Door::Door(const std::string& n)
    : DrawableObject(n)
{
    setType("door");
}

} // namespace MML
