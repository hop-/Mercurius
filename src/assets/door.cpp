#include "door.hpp"

namespace Assets
{

Door::
Door(const MML::Door* d, Core::Layer* l)
    : Object(d, l)
{}

void Door::
setupLogicObject()
{
    addCollider(true);
    addComponent(new DoorZone);
}

} // end of namespace Assets
