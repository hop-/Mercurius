#include "gui.hpp"
#include "gui_object.hpp"
#include <core/frame.hpp>

namespace Sdl
{

void Gui::draw()
{
    assert(0 != frame());
    for (Core::GuiObject* object : objects()) {
        frame()->drawTexture(object->texture());
    }
}

} // namespace Sdl
