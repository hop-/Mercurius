#include "layer.hpp"

#include "frame.hpp"
#include "logic.hpp"
#include "gui.hpp"

#include <cassert>

namespace Core
{

Layer::Layer(Gui* gui, Logic* logic,
        bool stopped, bool hidden, bool ignoreEvents)
    : m_gui(gui)
    , m_logic(logic)
    , m_stopped(stopped)
    , m_hidden(hidden)
    , m_ignoreEvent(ignoreEvents)
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

Command* Layer::getCommand(Event* event)
{
    assert(0 != event);
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
