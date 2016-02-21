#include "components.hpp"

namespace Core
{

void ViewPort::target(LogicObject* object)
{
    m_targetObject = object;
}

void ViewPort::aim()
{
    if (0 != m_targetObject) {
        // TODO aim viewPort position to m_targetObject position
    }
}

void ViewPort::update()
{
    aim();
}

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

void TextureRenderer::setState(int state)
{
    m_state = state;
    notify();
}

} // namespace Core
