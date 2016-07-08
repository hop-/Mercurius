#include "renderer.hpp"
#include "gui_object.hpp"
#include "frame.hpp"

namespace Core
{

Renderer::
Renderer(Frame* f)
    : m_frame(f)
    , m_drawingArea()
{
    assert(m_frame != 0);
    m_drawingArea = Rectangle(m_frame->width(), m_frame->height(), Position(0, 0));
}

void Renderer::
setDrawingArea(Rectangle rect)
{
    m_drawingArea = rect;
}

void Renderer::
drawObject(const GuiObject* g)
{
    assert(g != 0);
}

} // end of namespace Core
