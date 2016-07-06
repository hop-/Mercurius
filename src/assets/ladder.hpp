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
    Ladder(const MML::Ladder* s, Core::Layer* l);

private:
    void setupLogicObject() override;
};

} // namespace Assets

#endif //_ASSETS_LADDER_HPP_
