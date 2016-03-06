#include "gui_object.hpp"

namespace Core
{

GuiObject::GuiObject(){}

void GuiObject::setDimensions(int w, int h, float scale)
{
    m_width = w;
    m_height = h;
    m_scaleFactor = scale;
}

} // namespace Core
