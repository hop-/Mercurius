#include "logic.hpp"
#include "event.hpp"
#include "components.hpp"
#include "game.hpp"
#include "powers.hpp"

#include <cassert>

namespace Core
{

void Logic::update()
{
    for (auto* p: Powers::children()) {
        assert(0 != p);
        for (auto* object : LogicObjects::children()) {
            assert(0 != object);
            p->applyToObject(object);
        }
    }
    Game* game = Game::getInstance();
    assert(0 != game);
    Event* e = game->getEvent();
    if (0 != e) {
        for (auto* object : LogicObjects::children()) {
            assert(0 != object);
            object->process(e);
        }
    }
    for (auto* object : LogicObjects::children()) {
        assert(0 != object);
        object->update();
    }
}

Logic::Logic()
{
    Powers::addObject(new Gravity()); // TODO create using MML
    createViewPortObject();
    m_collider.setBounds(m_viewPort->component<ViewPort>()->movingArea()); // TODO tmp solution
}

Logic::~Logic()
{
}

void Logic::init()
{
    Base::ContainerObject<LogicObject>::init();
    Base::ContainerObject<NaturalPower>::init();
}

bool Logic::addLogicObject(LogicObject* object)
{
    assert(0 != object);
    // TODO either move to onObjectAdding, or remove onObjectAdding
    Collider* collider = object->component<Collider>();
    if (collider != 0) {
        m_collider.insert(object);
    }
    return Base::ContainerObject<LogicObject>::addObject(object);
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

void Logic::onObjectAdding(LogicObject* object)
{
    assert(0 != object);
    if (object->component<Collider>() != 0) {
        //m_sweepLine.insert(object);
    }
}

void Logic::updateObject(LogicObject* object, Position p)
{
    m_collider.update(object, p);
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
