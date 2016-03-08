#ifndef _SDL_DUDE_HPP_
#define _SDL_DUDE_HPP_

#include "object.hpp"

#include <mml/dude.hpp>

namespace Sdl
{

class Dude : public Object
{
public:
    Dude(const MML::Dude* d, Core::Layer* l)
        : Object(d, l)
    {
        init(); // TODO remove after adding as child to Layer
    }

private:
    virtual void init()
    {
        addLogicObject();
        addCollider();
        addGuiObject();
        addPhysics();
    }
};

} // namepsace Sdl

#endif // _SDL_DUDE_HPP_
