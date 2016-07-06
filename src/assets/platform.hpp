#ifndef _ASSETS_PLATFORM_HPP_
#define _ASSETS_PLATFORM_HPP_

#include "object.hpp"
#include "components.hpp"

#include <mml/platform.hpp>

namespace Assets
{

class Platform
    : public Object
{
public:
    Platform(const MML::Platform* d, Core::Layer* l);

private:
    void setupLogicObject() override;
};

} // namepsace Assets

#endif // _ASSETS_PLATFORM_HPP_
