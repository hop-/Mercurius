#include "gui_object.hpp"

namespace Core
{

GuiObject::GuiObject(Gui* parent, const std::string& config)
    : m_mml(config)
    , m_parent(parent)
{
    assert(0 != parent);
}

} // namespace Core
