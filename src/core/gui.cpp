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
        frame()->draw(object);
    }
}

Gui::~Gui()
{
}

} // namespace Core
