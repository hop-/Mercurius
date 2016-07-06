#include "ladder.hpp"

namespace Assets
{

Ladder::
Ladder(const MML::Ladder* s, Core::Layer* l)
    : ObjectArray(s, l)
{}

void Ladder::
setupLogicObject()
{
    addCollider(true);
    addComponent(new LadderZone);
}

} // end of namespace Assets
