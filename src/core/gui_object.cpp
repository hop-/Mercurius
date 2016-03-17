#include "gui_object.hpp"
#include "components.hpp"
#include "gui.hpp"

#include <cassert>

namespace Core
{

GuiObject::GuiObject(){}

void GuiObject::setDimensions(UserUnit w, UserUnit h, float scale)
{
    m_rect.setWidth(w);
    m_rect.setHeight(h);
    m_scaleFactor = scale;
}

void GuiObject::onNotify()
{
    m_rect.setPosition(textureRenderer()->objectPosition());
    m_state = textureRenderer()->state();
}

float GuiObject::scale() const
{
    return guiManager()->scale();
}

Rectangle GuiObject::rect() const
{
    return guiManager()->viewPort()->represent(m_rect);
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
