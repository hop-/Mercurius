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
    loadGuiObject(o);
    /*
    assert(0 != guiObject2Texture(o));
    assert(m_textures.end() == sdt::find(
                m_textures.begin()
                , m_textures.end()
                , guiObject2Texture(o)));
    m_textures.push_back(guiObject2Texture(o));
    */
}

void Gui::removeGuiObject(GuiObject* o)
{
    assert(0 != o);
    GuiObjects::iterator i =
        std::find(m_objects.begin(), m_objects.end(), o);
    assert(m_objects.end() != i);
    m_objects.erase(i);
    /*
    Texture* texture = guiObject2Texture(o);
    assert(0 != texture);
    Textures::iterator it =
        std::find(m_textures.begin(), m_textures.end(), texture);
    assert(m_textures.end() != it);
    m_textures.erase(it);
    */
}

} // namespace Core
