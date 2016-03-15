#include "gui_object.hpp"
#include "components.hpp"

namespace Core
{

GuiObject::GuiObject(){}

void GuiObject::setDimensions(UserUnit w, UserUnit h, float scale)
{
    m_width = w;
    m_height = h;
    m_scaleFactor = scale;
}

void GuiObject::onNotify()
{
    Position position =
        static_cast<Core::TextureRenderer*>(subject())->objectPosition();
    UserUnit x = position.x();
    m_x = x;
    UserUnit y = position.y();
    m_y = y;
    m_state =
        static_cast<Core::TextureRenderer*>(subject())->state();
}

} // namespace Core
