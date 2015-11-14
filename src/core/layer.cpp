#include "layer.hpp"

#include "frame.hpp"

namespace Core
{

Layer::Layer(Gui* gui, Logic* logic, Controls controls,
        bool stopped, bool hidden, bool ignoreEvents) :
    m_gui{gui},
    m_logic{logic},
    m_controls(controls),
    m_stopped{stopped},
    m_hidden{hidden},
    m_ignoreEvent{ignoreEvents}
{}

void Layer::changeControls(Controls controls)
{
    m_controls = controls;
}

Controls Layer::getControls()
{
    return m_controls;
}

Command* Layer::getCommand(Event* event)
{
    // TODO
}

void Layer::stop(bool stop)
{
    m_stopped = stop;
}

void Layer::hide(bool hide)
{
    m_hidden = hide;
}

void Layer::ignoreEvents(bool ignoreEvents)
{
    m_ignoreEvent = ignoreEvents;
}

bool Layer::isStopped()
{
    return m_stopped;
}

void Layer::update()
{
    // TODO
}

void Layer::draw(Frame* frame)
{
    // TODO
}

} /// namespace Core
