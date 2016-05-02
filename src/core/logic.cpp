#include "logic.hpp"
#include "components.hpp"
#include "powers.hpp"

#include <cassert>

namespace Core
{

void Logic::update()
{
    applyPowers();
    updateLogicObjects();
    m_collider.throwCollisionEvents();
}

void Logic::applyPowers()
{
    for (auto* p: Powers::children()) {
        assert(0 != p);
        for (auto* object : LogicObjects::children()) {
            assert(0 != object);
            p->applyToObject(object);
        }
    }
}

void Logic::updateLogicObjects()
{
    for (auto* object : LogicObjects::children()) {
        assert(0 != object);
        object->update();
    }
}

Logic::Logic()
    : m_collider()
{
    createViewPortObject();
    m_collider.setBounds(m_viewPort->component<ViewPort>()->movingArea()); // TODO tmp solution
}

Logic::~Logic()
{
}

void Logic::init()
{
    Powers::addObject(new Gravity()); // TODO create using MML
    Base::ContainerObject<LogicObject>::init();
    Base::ContainerObject<NaturalPower>::init();
}

bool Logic::addLogicObject(LogicObject* object)
{
    assert(0 != object);
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

void Logic::onObjectAdding(const LogicObject* object)
{
    assert(0 != object);
    Collider* collider = object->component<Collider>();
    if (collider != 0) {
        m_collider.insert(object);
    }
}

void Logic::updateObject(LogicObject* object, Position p)
{
    m_collider.update(object, p);
}

void Logic::createViewPortObject()
{
    m_viewPort = new LogicObject();
    ViewPort* component = ViewPort::getInstance();
    m_viewPort->addComponent(component);
}

void Logic::aimTo(LogicObject* l)
{
    assert(0 != l);
    m_viewPort->component<ViewPort>()->target(l);
}

} // namespace Core
