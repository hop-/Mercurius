#include "logic.hpp"
#include "event.hpp"
#include "components.hpp"
#include "game.hpp"

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
    m_sweepLine.run();
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

void Logic::addToViewPort(LogicObject* object)
{
    assert(0 != object);
    TextureRenderer* objectTR = object->component<TextureRenderer>();
    if (0 != objectTR) {
        m_viewPort->component<ViewPort>()->addObserver(objectTR);
    }
}

const ViewPort* Logic::viewPortComponent() const
{
    assert(0 != m_viewPort);
    assert(0 != m_viewPort->component<ViewPort>());
    return m_viewPort->component<ViewPort>();
}

void Logic::onObjectAdding(const LogicObject* object)
{
    if (object->component<Collider>() != 0) {
        m_sweepLine.insert(object);
    }
}

void Logic::updateSweepLine(const LogicObject* object)
{
    m_sweepLine.update(object);
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
