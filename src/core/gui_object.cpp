#include "gui_object.hpp"
#include "gui.hpp"

namespace Core
{

GuiObject::
GuiObject(Gui* parent)
    : m_parent(parent)
{
    assert(0 != parent);
    parent->addGuiObject(this);
}

void GuiObject::
setParent(Gui* parent)
{
    assert(0 != parent);
    m_parent->removeGuiObject(this);
    m_parent = parent;
}

} // namespace Core
