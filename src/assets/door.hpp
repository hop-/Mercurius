#ifndef _ASSETS_DOOR_HPP_
#define _ASSETS_DOOR_HPP_

#include "object.hpp"
#include "components.hpp"

#include <mml/door.hpp>

namespace Assets
{

class Door : public Object
{
public:
    Door(const MML::Door* d, Core::Layer* l);

private:
    void setupLogicObject() override;
};

} // namepsace Assets

#endif // _ASSETS_DOOR_HPP_
