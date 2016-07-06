#include "ground.hpp"

namespace Assets
{

Ground::
Ground(const MML::Ground* d, Core::Layer* l)
    : Object(d, l)
{}

void Ground::
setupLogicObject()
{
    addCollider();
}

} // end of namespace Assets
