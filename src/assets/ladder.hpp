#ifndef _ASSETS_LADDER_HPP_
#define _ASSETS_LADDER_HPP_

#include "object.hpp"

#include "mml/ladder.hpp"

namespace Assets
{

class Ladder
    :public Object
{
public:
    Ladder(const MML::Ladder* s, Core::Layer* l)
        : Object(s, l)
    {}

private:
    void setupLogicObject()
    {
        addCollider(true);
    }
};

} // namespace Assets

#endif //_ASSETS_LADDER_HPP_
