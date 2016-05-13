#ifndef _ASSETS_DOOR_HPP_
#define _ASSETS_DOOR_HPP_

#include "object.hpp"
#include "states.hpp"

#include <mml/door.hpp>

namespace Assets
{

class Door : public Object
{
public:
    Door(const MML::Door* d, Core::Layer* l)
        : Object(d, l)
    {}

private:
    void setupLogicObject()
    {
        addCollider(true);
    }
};

} // namepsace Assets

#endif // _ASSETS_DOOR_HPP_
