#include "components.hpp"
#include "events.hpp"
#include "frame.hpp"
#include "logic.hpp"

namespace Core
{

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
    if (m_movingArea.xMax() >= tmpRect.xMax()
            && m_movingArea.xMin() <= tmpRect.xMin()) {
        setX(p.x());
    }
    if (m_movingArea.yMax() >= tmpRect.yMax()
            && m_movingArea.yMin() <= tmpRect.yMin()) {
        setY(p.y());
    }
}

void ViewPort::onNotify()
{
    aim();
    notify();
}

void Physics::update()
{
    assert(0 != parent());
    Position position = parent()->position();
    if (m_velocity.magnitude() != 0) {
        position.move(m_velocity);
        parent()->requestNewPosition(position);
    }
}

void Collider::onNotify()
{}

void TextureRenderer::init()
{
    assert(0 != parent());
    if (0 != parent()->parent()) {
        dynamic_cast<Logic*>(parent()->parent())->addToViewPort(parent());
    }
    notify();
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
