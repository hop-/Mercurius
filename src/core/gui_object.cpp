#include "gui_object.hpp"
#include "components.hpp"
#include "gui.hpp"

#include <cassert>

namespace Core
{

GuiObject::GuiObject(){}

void GuiObject::setDimensions(UserUnit w, UserUnit h, float scale)
{
    m_realRect.setWidth(w);
    m_realRect.setHeight(h);
    m_scaleFactor = scale;
}

void GuiObject::onNotify()
{
    m_realRect.setPosition(textureRenderer()->objectPosition());
    m_state = textureRenderer()->state();
}

void GuiObject::updatePosInViewPort()
{
    m_rect = guiManager()->viewPort()->represent(m_realRect);
    onNotify(); // TODO wrong place just for test
}

const TextureRenderer* GuiObject::textureRenderer() const
{
    assert(0 != subject());
    return static_cast<const TextureRenderer*>(subject());
}

const Gui* GuiObject::guiManager() const
{
    assert(0 != dynamic_cast<const Gui*>(parent()));
    return dynamic_cast<const Gui*>(parent());
}

} // namespace Core
