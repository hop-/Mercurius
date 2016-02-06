#include "gui.hpp"

#include <algorithm>

namespace Core
{

void Gui::addGuiObject(GuiObject* o)
{
    assert(0 != o);
    assert(m_objects.end() ==
           std::find(m_objects.begin(), m_objects.end(), o));
    m_objects.push_back(o);
}

void Gui::removeGuiObject(GuiObject* o)
{
    assert(0 != o);
    GuiObjects::iterator i =
        std::find(m_objects.begin(), m_objects.end(), o);
    assert(m_objects.end() != i);
    m_objects.erase(i);
}

} // namespace Core
