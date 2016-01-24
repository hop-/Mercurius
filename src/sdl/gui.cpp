#include "gui.hpp"
#include "gui_object.hpp"
#include <core/frame.hpp>

namespace Sdl
{

void Gui::draw(Core::Frame* frame)
{
    assert(0 != frame);
    //SDL_Renderer* frameRenderer =
    //    static_cast<SDL_Renderer*>(frame->renderer());
    for (Core::GuiObject* object : objects()) {
        frame->drawTexture(object->texture());
    }
}

} // namespace Sdl
