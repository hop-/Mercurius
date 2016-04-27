#include "event_generator.hpp"
#include "events.hpp"

#include <core/events.hpp>
#include <core/event_manager.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>

namespace Assets
{

EventGenerator::GroundsOfObject EventGenerator::m_groundsOfObject;

EventGenerator::~EventGenerator()
{
    Core::ObjectCollision::removeCallbacks(this);
}

void EventGenerator::init()
{
    Core::ObjectCollision::registerCallback(
            &EventGenerator::ObjColl2OnSurface, this);
    Core::ObjectCollision::registerCallback(
            &EventGenerator::ObjColl2OnAir, this);
}

void EventGenerator::ObjColl2OnSurface(Base::Event* e)
{
    Core::ObjectCollision* oc = Core::ObjectCollision::cast(e);
    assert(0 != oc);
    if (oc->isTrigger()
            || oc->status() == Core::ObjectCollision::Status::Detached) {
        return;
    }
    if (oc->directionForFirst() != Core::Direction::Up
            && oc->directionForSecond() != Core::Direction::Up) {
        return;
    }
    const Core::LogicObject* o1;
    const Core::LogicObject* o2;
    if (oc->directionForFirst() == Core::Direction::Up) {
        o1 = oc->first();
        o2 = oc->second();
    } else {
        o1 = oc->second();
        o2 = oc->first();
    }
    assert(0 != o1);
    assert(0 != o2);
    if (0 == o1->component<Core::Physics>()) {
        return;
    }
    m_groundsOfObject[o1].push_back(o2);
    if (m_groundsOfObject[o1].size() == 1) {
        Core::EventManager::process(new OnSurface(o1));
    }
}

void EventGenerator::ObjColl2OnAir(Base::Event* e)
{
    Core::ObjectCollision* oc = Core::ObjectCollision::cast(e);
    assert(0 != oc);
    if (oc->isTrigger()
            || oc->status() == Core::ObjectCollision::Status::Attached) {
        return;
    }
    const Core::LogicObject* of;
    const Core::LogicObject* os;
    of = oc->first();
    os = oc->second();
    assert(0 != of);
    assert(0 != os);
    if (0 != of->component<Core::Physics>()) {
        if (m_groundsOfObject[of].size()) {
            m_groundsOfObject[of].remove(os);
            if (m_groundsOfObject[of].size() == 0) {
                Core::EventManager::process(new OnAir(of));
            }
        }
    }
    if (0 != os->component<Core::Physics>()) {
        if (m_groundsOfObject[os].size()) {
            m_groundsOfObject[os].remove(of);
            if (m_groundsOfObject[os].size() == 0) {
                Core::EventManager::process(new OnAir(os));
            }
        }
    }
}

} // namespace Assets
