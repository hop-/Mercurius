#include "gui.hpp"
#include "gui_object.hpp"
#include "frame.hpp"

#include <algorithm>

namespace Core
{

void Gui::draw()
{
    assert(0 != m_frame);
    for (auto* object : children()) {
        object->updatePosInViewPort(); // TODO must be called in other place
        frame()->prepareToDraw(object);
    }
}

Gui::~Gui()
{
}

} // namespace Core
