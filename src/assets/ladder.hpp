#ifndef _ASSETS_LADDER_HPP_
#define _ASSETS_LADDER_HPP_

#include "object_array.hpp"
#include "components.hpp"

#include <mml/ladder.hpp>

namespace Assets
{

class Ladder
    :public ObjectArray
{
public:
    Ladder(const MML::Ladder* s, Core::Layer* l)
        : ObjectArray(s, l)
    {}

private:
    void setupLogicObject()
    {
        addCollider(true);
        addComponent(new LadderZone);
    }
};

} // namespace Assets

#endif //_ASSETS_LADDER_HPP_
