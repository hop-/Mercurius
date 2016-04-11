#ifndef _ASSETS_STAIRS_HPP_
#define _ASSETS_STAIRS_HPP_

#include "object.hpp"

#include "mml/stairs.hpp"

namespace Assets
{

class Stairs
    :public Object
{
public:
    Stairs(const MML::Stairs* s, Core::Layer* l)
        : Object(s, l)
    {}

private:
    void setupLogicObject()
    {
        addCollider(true);
    }
};

} // namespace Assets

#endif //_ASSETS_STAIRS_HPP_
