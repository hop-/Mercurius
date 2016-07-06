#include "box.hpp"

namespace Assets
{

Box::
Box(const MML::MMLBox* b, Core::Layer* l)
    : Object(b, l)
{
}

void Box::
setupLogicObject()
{
    addPhysics();
    addCollider();
}

} // end of namespace Assets
