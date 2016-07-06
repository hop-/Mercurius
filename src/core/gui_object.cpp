#include "gui_object.hpp"
#include "components.hpp"
#include "gui.hpp"

#include <cassert>

namespace Core
{

GuiObject::
GuiObject()
    : m_textureLocation()
    , m_rect()
{}

void GuiObject::
setDimensions(UserUnit w, UserUnit h, float scale)
{
    m_rect.setWidth(w);
    m_rect.setHeight(h);
    m_scaleFactor = scale;
}

void GuiObject::
onNotify()
{
    m_rect.setPosition(textureRenderer()->objectPosition());
    m_state = textureRenderer()->state();
    m_direction = textureRenderer()->direction();
}

float GuiObject::
scale() const
{
    return guiManager()->scale();
}

const Rectangle& GuiObject::
realRect() const
{
    return m_rect;
}

UserUnit GuiObject::
width() const
{
    return m_rect.width();
}

UserUnit GuiObject::
height() const
{
    return m_rect.height();
}

int GuiObject::
priority() const
{
    return m_priority;
}

float GuiObject::
scaleFactor() const
{
    return m_scaleFactor;
}

void GuiObject::
setPriority(int priority)
{
    m_priority = priority;
}

HorizontalDirection GuiObject::
direction() const
{
    return m_direction;
}

UserUnit GuiObject::
x() const
{
    return m_rect.position().x();
}

UserUnit GuiObject::
y() const
{
    return m_rect.position().y();
}

int GuiObject::
state() const
{
    return m_state;
}

const std::string& GuiObject::
textureLocation() const
{
    return m_textureLocation;
}

void GuiObject::
setTextureLocation(const std::string& textureLocation)
{
    m_textureLocation = textureLocation;
}

Rectangle GuiObject::
rect() const
{
    assert(0 != guiManager()->viewPort());
    return guiManager()->viewPort()->represent(m_rect);
}

const TextureRenderer* GuiObject::
textureRenderer() const
{
    assert(0 != subject());
    return static_cast<const TextureRenderer*>(subject());
}

const Gui* GuiObject::
guiManager() const
{
    assert(0 != dynamic_cast<const Gui*>(parent()));
    return dynamic_cast<const Gui*>(parent());
}

} // namespace Core
