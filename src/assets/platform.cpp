#include "platform.hpp"

namespace Assets
{

Platform::
Platform(const MML::Platform* d, Core::Layer* l)
    : Object(d, l)
{}

void Platform::
setupLogicObject()
{
    addCollider();
    addComponent(new PlatformZone);
}

} // end of namepsace Assets
