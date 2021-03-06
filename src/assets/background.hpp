#ifndef _ASSETS_BACKGROUND_HPP_
#define _ASSETS_BACKGROUND_HPP_

#include "object.hpp"
#include "components.hpp"

#include <mml/background.hpp>

namespace Assets
{

class Background : public Object
{
public:
    Background(const MML::Background* b, Core::Layer* l);

private:
    void setupLogicObject();
};

} // namespace Asset

#endif // _ASSETS_BACKGROUND_HPP_
