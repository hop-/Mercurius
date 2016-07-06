#ifndef _ASSETS_GROUND_HPP_
#define _ASSETS_GROUND_HPP_

#include "object.hpp"

#include <mml/ground.hpp>

namespace Assets
{

class Ground : public Object
{
public:
    Ground(const MML::Ground* d, Core::Layer* l);

private:
    void setupLogicObject() override;
};

} // namepsace Assets

#endif // _ASSETS_GROUND_HPP_
