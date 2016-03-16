#ifndef _ASSETS_DUDE_HPP_
#define _ASSETS_DUDE_HPP_

#include "object.hpp"
#include "states.hpp"

#include <mml/dude.hpp>

namespace Assets
{

class Dude : public Object
{
public:
    Dude(const MML::Dude* d, Core::Layer* l)
        : Object(d, l)
    {}

private:
    virtual void init()
    {
        addLogicObject();
        addCollider();
        addGuiObject();
        addPhysics();
        addState(new Standing);
    }
};

} // namepsace Assets

#endif // _ASSETS_DUDE_HPP_
