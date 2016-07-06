#include "gui.hpp"
#include "gui_object.hpp"
#include "frame.hpp"

namespace Core
{

Gui::
Gui()
    : Base::ContainerObject<GuiObject>()
    , m_viewPort(0)
    , m_frame(0)
{}

float Gui::
scale() const
{
    float widthScale = float(frame()->width())
        / float(viewPort()->width());
    float heightScale = float(frame()->height())
        / float(viewPort()->height());
    return (widthScale > heightScale) ? heightScale : widthScale;
}


void Gui::
draw()
{
    assert(0 != m_frame);
    for (auto* object : children()) {
        frame()->prepareToDraw(object);
    }
}

Frame* Gui::
frame() const
{
    return m_frame;
}

void Gui::
setFrame(Frame* frame)
{
    assert(0 != frame);
    m_frame = frame;
}

void Gui::
setViewPort(const Rectangle* viewPort)
{
    assert(0 != viewPort);
    m_viewPort = viewPort;
}

const Rectangle* Gui::
viewPort() const
{
    return m_viewPort;
}

Gui::~Gui()
{
}

} // namespace Core
