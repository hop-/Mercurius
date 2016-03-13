#ifndef _ASSETS_BOX_HPP_
#define _ASSETS_BOX_HPP_

#include "object.hpp"

#include <mml/mml_box.hpp>

namespace Assets
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

} // namespace Asset

#endif // _ASSETS_BOX_HPP_
