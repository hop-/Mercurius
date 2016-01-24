#include "layer.hpp"

#include "frame.hpp"
#include "logic.hpp"
#include "gui.hpp"

#include <cassert>

namespace Core
{

Layer::Layer(Gui* gui, Logic* logic, Controls controls,
        bool stopped, bool hidden, bool ignoreEvents)
    : m_gui(gui)
    , m_logic(logic)
    , m_controls(controls)
    , m_stopped(stopped)
    , m_hidden(hidden)
    , m_ignoreEvent(ignoreEvents)
{
    assert(0 != gui);
    assert(0 != logic);
}

void Layer::changeControls(Controls controls)
{
    m_controls = controls;
}

Command* Layer::getCommand(Event* event)
{
    assert(0 != event);
    return m_controls.getCommand(event);
}

void Layer::update()
{
    m_logic->update();
}

void Layer::draw(Frame* frame)
{
    if (!m_hidden) {
        m_gui->draw(frame);
    }
}

} // namespace Core
