#include "components.hpp"
#include "gui_object.hpp"

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
    parent()->setPosition(position);
}

void TextureRenderer::init()
{
    notify();
}

void TextureRenderer::onNotify()
{
    m_position = parent()->position();
    notify();
}

void TextureRenderer::setState(int state)
{
    assert(0 < state);
    assert(m_numberOfStates > state);
    m_state = static_cast<unsigned>(state);
    notify();
}

} // namespace Core
