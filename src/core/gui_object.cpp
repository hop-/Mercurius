#include "gui_object.hpp"

namespace Core
{

GuiObject::GuiObject(){}

void GuiObject::setDimensions(Rectangle rect, float scale)
{
    setSrcRect(rect);
    setDestRect(rect.scaled(scale));
}

} // namespace Core
