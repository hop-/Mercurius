#ifndef _SDL_BOX_HPP_
#define _SDL_BOX_HPP_

#include "object.hpp"

#include <mml/mml_box.hpp>

namespace Sdl
{

class Box : public Object
{
public:
    Box(const MML::MMLBox* b, Core::Layer* l)
        : Object(b, l)
    {
    }

private:
    virtual void init()
    {
        addLogicObject();
        addCollider();
        addGuiObject();
    }

};

} // namespace Sdl

#endif // _SDL_BOX_HPP_
