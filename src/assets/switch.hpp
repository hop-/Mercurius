#ifndef _ASSETS_SWITCH_HPP_
#define _ASSETS_SWITCH_HPP_

#include "object.hpp"
#include "states.hpp"
#include "components.hpp"

#include <mml/switch.hpp>

namespace Assets
{

class Switch : public Object
{
public:
    Switch(const MML::Switch* d, Core::Layer* l);

private:
    void setupLogicObject() override;
};

} // namepsace Assets

#endif // _ASSETS_SWITCH_HPP_
