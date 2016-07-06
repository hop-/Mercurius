#include "object_collider.hpp"

#include "logic_object.hpp"
#include "components.hpp"
#include "position.hpp"
#include "events.hpp"

#include <base/event_manager.hpp>

namespace Core
{

ObjectCollider::
ObjectCollider()
    : m_quadTree(0, Rectangle(0, 0, Position(0, 0)))
    , m_contactedPairs()
    , m_collidedPairs()
{}

ObjectCollider::
ObjectCollider(Rectangle bounds)
    : m_quadTree(0, bounds)
    , m_contactedPairs()
    , m_collidedPairs()
{}

void ObjectCollider::
setBounds(Rectangle bounds)
{
    m_quadTree.setBounds(bounds);
}

void ObjectCollider::
insert(const LogicObject* object)
{
    assert(0 != object);
    assert(0 != object->component<Collider>());
    m_quadTree.insert(object->component<Collider>());
}

void ObjectCollider::
update(LogicObject* object, Position p)
{
    //TODO performance improvement
    assert(0 != object);
    assert(0 != object->component<Collider>());
    Collider* c = object->component<Collider>();
    m_quadTree.remove(c);
    Position pOld = object->position();
    Position positionWithNewX(p.x(), pOld.y());
    object->setPosition(positionWithNewX);
    m_quadTree.insert(c);
    EngineUnit maxDX = 0;
    for (const auto* collider : m_quadTree.retreive(c)) {
        LogicObject* collided = collider->parent();
        if (collided == object
                || !collider->rect().intersects(c->rect())) {
            continue;
        }
        m_collidedPairs.push_back(Pair{object, collided});
        if (!c->isTrigger(collided) && !collider->isTrigger(object)) {
            EngineUnit dX;
            if (p.x() - pOld.x() > 0) {
                // moved right
                dX = c->rect().right()
                    - collider->rect().left();
            } else {
                // moved left
                dX = collider->rect().right()
                    - c->rect().left();
            }
            if (maxDX < dX) {
                maxDX = dX;
            }
        }
    }
    if (p.x() - pOld.x() > 0) {
        p.setX(p.x() - maxDX);
    } else {
        p.setX(p.x() + maxDX);
    }
    m_quadTree.remove(c);
    object->setPosition(p);
    m_quadTree.insert(c);
    EngineUnit maxDY = 0;
    for (const auto* collider : m_quadTree.retreive(c)) {
        LogicObject* collided = collider->parent();
        if (collided == object
                || !collider->rect().intersects(c->rect())) {
            continue;
        }
        m_collidedPairs.push_back(Pair{object, collided});
        if (!c->isTrigger(collided) && !collider->isTrigger(object)) {
            EngineUnit dy;
            if (p.y() - pOld.y() > 0) {
                // moved up
                dy = c->rect().top()
                    - collider->rect().bottom();
            } else {
                // moved down
                dy = collider->rect().top()
                    - c->rect().bottom();
            }
            if (maxDY < dy) {
                maxDY = dy;
            }
        }
    }
    if (p.y() - pOld.y() > 0) {
        p.setY(p.y() - maxDY);
    } else {
        p.setY(p.y() + maxDY);
    }
    m_quadTree.remove(c);
    object->setPosition(p);
    Physics* ph = object->component<Physics>();
    // TODO: need to move to the other place
    // stopping moving in collided direction
    if (ph != 0) {
        if (maxDX != 0) {
            ph->stopX();
        }
        if (maxDY != 0) {
            ph->stopY();
        }
    }
    m_quadTree.insert(c);
    m_collidedPairs.unique();
}

void ObjectCollider::
remove(const LogicObject* object)
{
    assert(0 != object);
    assert(0 != object->component<Collider>());
    m_quadTree.remove(object->component<Collider>());
}

void ObjectCollider::
throwCollisionEvents()
{
    for (Pairs::iterator pair = m_contactedPairs.begin()
            ; pair != m_contactedPairs.end()
            ; ++pair) {
        assert(pair->first->component<Collider>());
        assert(pair->second->component<Collider>());
        if (!pair->first->component<Collider>()->rect().intersects(
                    pair->second->component<Collider>()->rect())
                && !pair->first->component<Collider>()->rect().contacts(
                    pair->second->component<Collider>()->rect())) {
            Base::EventManager::process(new ObjectCollision(
                    (*pair)
                    , ObjectCollision::Status::Detached));
            Pairs::iterator tmpIt = pair;
            --pair;
            m_contactedPairs.erase(tmpIt);
        }
    }

    for (const auto& pair : m_collidedPairs) {
        if (find(m_contactedPairs.begin(), m_contactedPairs.end(), pair)
                == m_contactedPairs.end()) {
            m_contactedPairs.push_back(pair);
            Base::EventManager::process(new ObjectCollision(
                            pair
                            , ObjectCollision::Status::Attached));
        }
    }
    m_collidedPairs.clear();
}

bool ObjectCollider::
areCollided(const LogicObject* o1
        , const LogicObject* o2) const
{
    Pair p1{o1, o2};
    Pair p2{o2, o1};
    return (std::find(m_contactedPairs.begin(),
                m_contactedPairs.end(),
                p1) != m_contactedPairs.end()
            || std::find(m_contactedPairs.begin(),
                m_contactedPairs.end(),
                p2) != m_contactedPairs.end());
}

} // namespace Core
