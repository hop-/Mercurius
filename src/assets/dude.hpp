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
    Dude(const MML::Dude* d, Core::Layer* l);

private:
    void setupLogicObject() override;
};

} // namepsace Assets

#endif // _ASSETS_DUDE_HPP_
