#include "switch.hpp"

namespace Assets
{

Switch::
Switch(const MML::Switch* d, Core::Layer* l)
    : Object(d, l)
{}

void Switch::
setupLogicObject()
{
    addCollider(true);
    addComponent(new SwitchZone);
    addState(new SwitchInactive);
    addState(new SwitchState(false));
}

} // end of namepsace Assets
