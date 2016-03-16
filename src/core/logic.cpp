#include "logic.hpp"
#include "event.hpp"
#include "game.hpp"
#include "components.hpp"

#include <cassert>

namespace Core
{

void Logic::update()
{
    Game* game = Game::getInstance();
    assert(0 != game);
    Event* e = game->getEvent();
    if (0 != e) {
        for (auto* object : children()) {
            assert(0 != object);
            object->process(e);
        }
    }
    for (auto* object : children()) {
        assert(0 != object);
        object->update();
    }
}


Logic::Logic()
{
    createViewPortObject();
}

Logic::~Logic()
{
}

const LogicObject* Logic::viewPort() const
{
    assert(0 != m_viewPort);
    return m_viewPort;
}

const ViewPort* Logic::viewPortComponent() const
{
    assert(0 != m_viewPort);
    assert(0 != m_viewPort->component<ViewPort>());
    return m_viewPort->component<ViewPort>();
}

void Logic::createViewPortObject()
{
    m_viewPort = new LogicObject();
    ViewPort* component = new ViewPort();
    m_viewPort->addComponent(component);
}

void Logic::aimTo(LogicObject* l)
{
    assert(0 != l);
    m_viewPort->component<ViewPort>()->target(l);
}

} // namespace Core
