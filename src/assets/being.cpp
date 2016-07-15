#include "being.hpp"

namespace Assets
{

Being::
Being(const MML::Being* b, Core::Layer* l)
    : Object(b, l)
{}

void Being::
setupLogicObject()
{
    addPhysics();
    addCollider();
}

} // namespace Assets
