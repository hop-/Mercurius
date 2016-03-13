#ifndef _ASSETS_BACKGROUND_HPP_
#define _ASSETS_BACKGROUND_HPP_

#include "object.hpp"

#include <mml/background.hpp>

namespace Assets
{

class Background : public Object
{
public:
    Background(const MML::Background* b, Core::Layer* l)
        : Object(b, l)
    {
    }

private:
    virtual void init()
    {
        addLogicObject();
        addGuiObject();
    }

};

} // namespace Asset

#endif // _ASSETS_BACKGROUND_HPP_
