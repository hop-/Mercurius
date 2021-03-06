#include "layer.hpp"

#include "frame.hpp"
#include "logic.hpp"
#include "gui.hpp"

#include <cassert>

namespace Core
{

static unsigned s_layer_id = 0;

unsigned Layer::maxId()
{
    return s_layer_id;
}

Layer::Layer(Gui* gui, Logic* logic,
        bool stopped, bool hidden, bool ignoreEvents)
    : m_gui(gui)
    , m_logic(logic)
    , m_stopped(stopped)
    , m_hidden(hidden)
    , m_ignoreEvent(ignoreEvents)
    , m_id(s_layer_id++)
{
    assert(0 != gui);
    assert(0 != logic);
    m_gui->setParent(this);
    m_logic->setParent(this);
    m_gui->setViewPort(m_logic->viewPortComponent());
}

Layer::~Layer()
{
    assert(0 != m_gui);
    assert(0 != m_logic);
    delete m_gui;
    m_gui = 0;
    delete m_logic;
    m_logic = 0;
}

unsigned Layer::
id() const
{
    return m_id;
}

void Layer::
stop(bool stop)
{
    m_stopped = stop;
}

void Layer::
hide(bool hide)
{
    m_hidden = hide;
}

void Layer::
ignoreEvents(bool ignoreEvents)
{
    m_ignoreEvent = ignoreEvents;
}

bool Layer::
isStopped() const
{
    return m_stopped;
}

const Logic* Layer::
logic() const
{
    return m_logic;
}

Gui* Layer::
gui()
{
    return m_gui;
}


Command* Layer::getCommand(Event*)
{
    return 0;
}

void Layer::update()
{
    m_logic->update();
}

void Layer::draw()
{
    if (!m_hidden) {
        m_gui->draw();
    }
}

void Layer::initObjectPost()
{
    assert(0 != m_gui);
    m_gui->init();
    assert(0 != m_logic);
    m_logic->init();
}

bool Layer::addGuiObject(GuiObject* g)
{
    assert(0 != g);
    assert(0 != m_gui);
    g->setParent(m_gui);
    return m_gui->addObject(g);
}

bool Layer::addLogicObject(LogicObject* l)
{
    assert(0 != l);
    assert(0 != m_logic);
    l->setParent(m_logic);
    return m_logic->addLogicObject(l);
}

void Layer::aimTo(LogicObject* l)
{
    assert(0 != l);
    assert(0 != m_logic);
    m_logic->aimTo(l);
}

} // namespace Core
