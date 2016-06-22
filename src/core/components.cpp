#include "components.hpp"
#include "events.hpp"
#include "frame.hpp"
#include "logic.hpp"
#include "events.hpp"

#include <base/event_manager.hpp>

namespace Core
{

template<>
ViewPort* Base::Singleton<ViewPort>::m_s_instance = 0;

ViewPort::ViewPort()
    : m_movingArea(UserUnit(1500)
            , UserUnit(1500)
            , Position(UserUnit(-200), UserUnit(-300)))    // TODO TMP for testing
{
    setWidth(UserUnit(1200));
    setHeight(UserUnit(900));
    setPosition(m_movingArea.position());
}

void ViewPort::target(LogicObject* object)
{
    assert(0 != object);
    object->addObserver(this);
    onNotify();
}

void ViewPort::aim()
{
    assert(0 != target());
    Position p(target()->position().x() - middleX()
            , target()->position().y() - middleY());
    Rectangle tmpRect(width(), height(), p);
    if (m_movingArea.right() >= tmpRect.right()
            && m_movingArea.left() <= tmpRect.left()) {
        setX(p.x());
    }
    if (m_movingArea.top() >= tmpRect.top()
            && m_movingArea.bottom() <= tmpRect.bottom()) {
        setY(p.y());
    }
}

void ViewPort::onNotify()
{
    aim();
    notify();
}

Physics::Physics()
    : m_grounds()
{
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<Physics>(this
                , &Physics::onCollisionEnter));
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<Physics>(this
                , &Physics::onCollisionExit));
}

void Physics::update()
{
    assert(0 != Component::parent());
    Position position = Component::parent()->position();
    if (m_velocity.magnitude() != 0) {
        position.move(m_velocity);
        Component::parent()->requestNewPosition(position);
    }
}

void Physics::onCollisionEnter(Base::Event* e)
{
    ObjectCollision* oc = ObjectCollision::cast(e);
    assert(0 != oc);
    LogicObject* owner = Component::parent();
    if (oc->isTrigger()
            || oc->status() == ObjectCollision::Status::Detached
            || !oc->contains(owner)) {
        return;
    }
    const LogicObject* g;
    if (oc->first() == owner) {
        if (oc->directionForFirst() != Direction::Up) {
            return;
        }
        g = oc->second();
    } else {
        if (oc->directionForSecond() != Direction::Up) {
            return;
        }
        g = oc->first();
    }
    assert(0 != g);
    m_grounds.push_back(g);
    if (m_grounds.size() == 1) {
        Base::EventManager::process(new OnSurface(owner));
    }
}

void Physics::onCollisionExit(Base::Event* e)
{
    ObjectCollision* oc = ObjectCollision::cast(e);
    assert(0 != oc);
    LogicObject* owner = Component::parent();
    if (oc->isTrigger()
            || oc->status() == ObjectCollision::Status::Attached
            || !oc->contains(owner)) {
        return;
    }
    m_grounds.remove(oc->another(owner));
    if (m_grounds.size() == 0) {
        Base::EventManager::process(new OnAir(owner));
    }
}

void Collider::onNotify()
{}

bool Collider::isTrigger(const LogicObject* object) const
{
    return (isTrigger()
            || std::find(m_triggerObjects.begin()
                , m_triggerObjects.end()
                , object) != m_triggerObjects.end());
}

Position Collider::position() const
{
    return parent()->position() + m_offset;
}

void Collider::addTriggerObject(const LogicObject* object)
{
    if (std::find(m_triggerObjects.begin()
                , m_triggerObjects.end()
                , object) == m_triggerObjects.end()) {
        m_triggerObjects.push_back(object);
    }
}

void Collider::removeTriggerObject(const LogicObject* object)
{
    assert(0 != parent());
    assert(0 != parent()->parent());
    if (parent()->parent<Logic>()->checkCollision(parent(), object)) {
        return; // TODO this part may contain bug
    }
    m_triggerObjects.remove(object);
}

void Collider::onParentSet()
{
    m_scaleFactor = parent()->scale();
    scaleSizes();
}

void TextureRenderer::init()
{
    assert(0 != parent());
    if (0 != parent()->parent()) {
        dynamic_cast<Logic*>(parent()->parent())->addToViewPort(parent());
    }
    assert(0 != parent());
    m_position = parent()->position();
    notify();
}

void TextureRenderer::onParentSet()
{
    m_scaleFactor = parent()->scale();
}

void TextureRenderer::onNotify()
{
    assert(0 != parent());
    m_position = parent()->position();
    notify();
}

void TextureRenderer::setState(int state)
{
    assert(0 < state);
    assert(m_numberOfStates > state);
    m_state = static_cast<unsigned>(state);
    notify();
}

} // namespace Core
