#include "components.hpp"
#include "events.hpp"
#include "frame.hpp"
#include "logic.hpp"
#include "events.hpp"
#include "animation_controller.hpp"

#include <base/event_manager.hpp>

namespace Core
{

Position Transform::
position() const
{
    return m_position;
}

float Transform::
scaleFactor() const
{
    return m_scale;
}

void Transform::
setPosition(Position p)
{
    m_position = p;
    notify();
}

void Transform::
setScaleFactor(float s)
{
    m_scale = s;
}

ViewPort::
ViewPort()
    : m_movingArea()
{
    setWidth(UserUnit(1200));
    setHeight(UserUnit(900));
    setPosition(m_movingArea.position());
}

void ViewPort::
target(LogicObject* object)
{
    assert(0 != object);
    object->addObserverToComponent<Transform>(this);
    onNotify();
}

void ViewPort::
setMovingArea(Rectangle area)
{
    m_movingArea = area;
    setPosition(area.position());
}

Rectangle ViewPort::
movingArea() const
{
    return m_movingArea;
}

void ViewPort::
aim()
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

EngineUnit ViewPort::
middleX() const
{
    return (right() - left()) / 2;
}

EngineUnit ViewPort::
middleY() const
{
    return (top() - bottom()) / 2;
}

const LogicObject* ViewPort::
target() const
{
    assert(0 != dynamic_cast<const Component*>(subject()));
    return static_cast<const Component*>(subject())->parent();
}

void ViewPort::
onNotify()
{
    aim();
    notify();
}

Physics::
Physics()
    : m_grounds()
{
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<Physics>(this
                , &Physics::onCollisionEnter));
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<Physics>(this
                , &Physics::onCollisionExit));
}

float Physics::
gravityScale() const
{
    return m_gravityScale;
}

void Physics::
setGravityScale(float gravityScale)
{
    m_gravityScale = gravityScale;
}

Vector Physics::
velocity() const
{
    return m_velocity;
}

void Physics::
setVelocity(const Vector& velocity)
{
    m_velocity = velocity;
}

void Physics::
addVelocity(const Vector& velocity)
{
    m_velocity += velocity;
}

void Physics::
applyGravity(const Vector& gravity)
{
    if (isOnSurface()) {
        return;
    }
    m_velocity += gravity * m_gravityScale;
}

void Physics::
stopX()
{
    Vector v = m_velocity;
    v.setX(0);
    setVelocity(v);
}

void Physics::
stopY()
{
    Vector v = m_velocity;
    v.setY(0);
    setVelocity(v);
}

void Physics::
update()
{
    assert(0 != Component::parent());
    Position position = Component::parent()->position();
    if (m_velocity.magnitude() != 0) {
        position.move(m_velocity);
        logic()->updateObject(Component::parent(), position);
    }
}

void Physics::
onCollisionEnter(Base::Event* e)
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

void Physics::
onCollisionExit(Base::Event* e)
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

bool Physics::
isOnSurface()
{
    return m_grounds.size();
}

bool Collider::
isTrigger(const LogicObject* object) const
{
    return (isTrigger()
            || std::find(m_triggerObjects.begin()
                , m_triggerObjects.end()
                , object) != m_triggerObjects.end());
}

Position Collider::
position() const
{
    return parent()->position() + m_offset;
}

Rectangle Collider::
rect() const
{
    return Rectangle(m_width, m_height, position());
}

void Collider::
setOffset(Position offset)
{
    m_offset = offset;
}

void Collider::
setOffset(UserUnit x, UserUnit y)
{
    m_offset = Position(x, y);
}

void Collider::
setSizes(UserUnit width, UserUnit height)
{
    m_width = width;
    m_height = height;
    scaleSizes();
}

UserUnit Collider::
width() const
{
    return m_width;
}

UserUnit Collider::
height() const
{
    return m_height;
}

bool Collider::
isTrigger() const
{
    return m_isTrigger;
}

void Collider::
trigger(bool isTrigger)
{
    m_isTrigger = isTrigger;
}
void Collider::
addTriggerObject(const LogicObject* object)
{
    if (std::find(m_triggerObjects.begin()
                , m_triggerObjects.end()
                , object) == m_triggerObjects.end()) {
        m_triggerObjects.push_back(object);
    }
}

void Collider::
removeTriggerObject(const LogicObject* object)
{
    assert(0 != parent());
    assert(0 != parent()->parent());
    if (parent()->parent<Logic>()->checkCollision(parent(), object)) {
        return; // TODO this part may contain bug
    }
    m_triggerObjects.remove(object);
}

void Collider::
onParentSet()
{
    m_scaleFactor = parent()->scale();
    scaleSizes();
}

void Collider::
scaleSizes()
{
    m_width = m_width * float(m_scaleFactor);
    m_height = m_height * float(m_scaleFactor);
}

void TextureRenderer::
setSizes(UserUnit w, UserUnit h)
{
    m_width = w;
    m_height = h;
}

UserUnit TextureRenderer::
width() const
{
    return m_width;
}

UserUnit TextureRenderer::
height() const
{
    return m_height;
}

Rectangle TextureRenderer::
rect() const
{
    return Rectangle(m_width, m_height, m_position)
        .scaled(scaleFactor());
}

void TextureRenderer::
setStateNumber(int numberOfStates)
{
    m_numberOfStates = numberOfStates;
}

HorizontalDirection TextureRenderer::
direction() const
{
    return m_direction;
}

float TextureRenderer::
scaleFactor() const
{
    return m_scaleFactor;
}

void TextureRenderer::
setDirection(HorizontalDirection d)
{
    m_direction = d;
    notify();
}

int TextureRenderer::
state() const
{
    return static_cast<int>(m_state);
}

Position TextureRenderer::
objectPosition() const
{
    return parent()->position();
}

void TextureRenderer::
init()
{
    assert(0 != parent());
    if (0 != parent()->parent()) {
        dynamic_cast<Logic*>(parent()->parent())->addToViewPort(parent());
    }
    addObserverToComponent<Transform>(this);
    onNotify();
}

void TextureRenderer::
onParentSet()
{
    m_scaleFactor = parent()->scale();
}

void TextureRenderer::
onNotify()
{
    assert(0 != parent());
    m_position = parent()->position();
    notify();
}

void TextureRenderer::
setState(int state)
{
    assert(0 < state);
    assert(m_numberOfStates > state);
    m_state = static_cast<unsigned>(state);
    notify();
}

void ArrayObject::
init()
{
    Collider* c = parent()->component<Collider>();
    if (0 != c) {
        c->setSizes(c->width() * m_columns, c->height() * m_rows);
    }
    // TODO add gui part
}

int ArrayObject::
rows() const
{
    return m_rows;
}

void ArrayObject::
setRows(int rows)
{
    m_rows = rows;
}

int ArrayObject::
columns() const
{
    return m_columns;
}

void ArrayObject::
setColumns(int columns)
{
    m_columns = columns;
}

Animator::
Animator(AnimationController* c)
    : m_controller(c)
{
    assert(0 != c);
}

void Animator::
update()
{
    assert(0 != m_controller);
    m_controller->update();
}

} // namespace Core
