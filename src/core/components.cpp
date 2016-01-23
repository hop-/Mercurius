#include "components.hpp"

namespace Core
{

void Physics::update()
{
    Position position = parent()->position();
    position.move(m_velocity);
}

void TextureRenderer::init()
{
    // TODO init
    // TODO add observer GuiObject
    notify();
}

} // namespace Core
