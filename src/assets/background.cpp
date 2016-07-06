#include "background.hpp"

namespace Assets {

Background::
Background(const MML::Background* b, Core::Layer* l)
    : Object(b, l)
{
}

void Background::
setupLogicObject()
{
    addComponent(new CameraFollower);
}

} // end of namespace
