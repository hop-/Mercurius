#include "components.hpp"

namespace Core
{

void Physics::update()
{
    // TODO some physical calculations
}

void TextureRenderer::init()
{
    // TODO init
    // TODO add observer GuiObject
    changeState();
}

void TextureRenderer::update()
{
    if (stateHasBeenChaned()) {
        notify();
    }
    resetState();
}


} // namespace Core
