#include "object_collider.hpp"

#include "logic_object.hpp"
#include "components.hpp"
#include "position.hpp"
#include "game.hpp"
#include "event_manager.hpp"
#include "events.hpp"

namespace Core
{

ObjectCollider::ObjectCollider()
    : m_quadTree(0, Rectangle(0, 0, Position(0, 0)))
{}

ObjectCollider::ObjectCollider(Rectangle bounds)
    : m_quadTree(0, bounds)
{}

void ObjectCollider::setBounds(Rectangle bounds)
{
    m_quadTree.setBounds(bounds);
}

void ObjectCollider::insert(const LogicObject* object)
{
    assert(0 != object);
    assert(0 != object->component<Collider>());
    m_quadTree.insert(object->component<Collider>());
}

void ObjectCollider::update(LogicObject* object, Position p)
{
    //TODO performance improvement
    assert(0 != object);
    assert(0 != object->component<Collider>());
    Collider* c = object->component<Collider>();
    m_quadTree.remove(c);
    Position pOld = c->rect().position();
    Position positionWithNewX(p.x(), pOld.y());
    object->setPosition(positionWithNewX);
    m_quadTree.insert(c);
    EngineUnit maxDX = 0;
    for (const auto* collider
            : m_quadTree.retreive(c)) {
        LogicObject* collieded = collider->parent();
        if (collieded == object
                || !collider->rect().intersects(c->rect())) {
            continue;
        }
        //Game::getInstance()->eventManager()
        //      ->push(new ObjectCollision(
        //            ObjectCollision::ObjectPair{object, collieded}
        //            , ObjectCollision::Status::Collided));
        m_currentCollidedPairs.push_back(Pair{object, collieded});
        if (!c->isTrigger() && !collider->isTrigger()) {
            EngineUnit dX;
            if (p.x() - pOld.x() > 0) {
                // moved right
                dX = c->rect().xMax()
                    - collider->rect().xMin();
            } else {
                // moved left
                dX = collider->rect().xMax()
                    - c->rect().xMin();
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
    for (const auto* collider
            : m_quadTree.retreive(c)) {
        LogicObject* collieded = collider->parent();
        if (collieded == object
                || !collider->rect().intersects(c->rect())) {
            continue;
        }
        m_currentCollidedPairs.push_back(Pair{object, collieded});
        if (!c->isTrigger() && !collider->isTrigger()) {
            EngineUnit dy;
            if (p.y() - pOld.y() > 0) {
                // moved up
                dy = c->rect().yMax()
                    - collider->rect().yMin();
            } else {
                // moved down
                dy = collider->rect().yMax()
                    - c->rect().yMin();
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
    // May be need to move in other place
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
}

void ObjectCollider::remove(const LogicObject* object)
{
    assert(0 != object);
    assert(0 != object->component<Collider>());
    m_quadTree.remove(object->component<Collider>());
}

void ObjectCollider::throwCollisionEvents()
{
    for (const auto& pair : m_currentCollidedPairs) {
        bool found = false;
        for (Pairs::iterator existPair = m_collidedPairs.begin()
                ; existPair != m_collidedPairs.end()
                ; ++existPair) {
            if ((pair.first == existPair->first
                        && pair.second == existPair->second)
                    || (pair.first == existPair->second
                        && pair.second == existPair->first))
            {
                m_collidedPairs.erase(existPair);
                found = true;
                break;
            }
        }
        if (!found) {
            Game::getInstance()->eventManager()
                ->push(new ObjectCollision(
                            pair
                            , ObjectCollision::Status::Attached));
        }
    }
    for (const auto& existPair : m_collidedPairs) {
        Game::getInstance()->eventManager()->push(new ObjectCollision(
                    existPair
                    , ObjectCollision::Status::Detached));
    }
    m_collidedPairs = m_currentCollidedPairs;
    m_currentCollidedPairs.clear();
}

} // namespace Core
