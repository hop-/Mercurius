#ifndef _ASSETS_DUDE_HPP_
#define _ASSETS_DUDE_HPP_

#include "object.hpp"

#include <core/states.hpp>
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
    void setupLogicObject()
    {
        addCollider();
        addPhysics();
        addState(new Core::Standing);
    }
};

} // namepsace Assets

#endif // _ASSETS_DUDE_HPP_
