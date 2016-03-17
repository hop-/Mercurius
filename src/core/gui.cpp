#include "gui.hpp"
#include "gui_object.hpp"
#include "frame.hpp"

namespace Core
{

float Gui::scale() const
{
    float widthScale = float(frame()->width())
        / float(viewPort()->width());
    float heightScale = float(frame()->height())
        / float(viewPort()->height());
    return (widthScale > heightScale) ? heightScale : widthScale;
}


void Gui::draw()
{
    assert(0 != m_frame);
    for (auto* object : children()) {
        frame()->prepareToDraw(object);
    }
}

Gui::~Gui()
{
}

} // namespace Core
