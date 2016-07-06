#include "dude.hpp"

namespace Assets
{

Dude::
Dude(const MML::Dude* d, Core::Layer* l)
    : Object(d, l)
{
}

void Dude::
setupLogicObject()
{
    addCollider();
    addPhysics();
    addState(new LayerChanger);
    addState(new Standing);
    addState(new OnGround); // contains bug
}

} // end of namespace Assets
