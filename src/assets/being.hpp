#ifndef _ASSETS_BEING_HPP_
#define _ASSETS_BEING_HPP_

#include "object.hpp"

#include <mml/being.hpp>

namespace Assets
{

class Being
    : public Object
{
public:
    Being(const MML::Being* b, Core::Layer* l);

private:
    void setupLogicObject() override;
};

} // namespace Assets

#endif //_ASSETS_BEING_HPP_
