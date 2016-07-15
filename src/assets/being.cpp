#include "being.hpp"
#include "components.hpp"

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
    addComponent(new BeingController());
}

} // namespace Assets
