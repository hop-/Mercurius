#include "event_generator.hpp"
#include "events.hpp"

#include <base/event_manager.hpp>
#include <core/events.hpp>
#include <core/logic_object.hpp>
#include <core/components.hpp>

namespace Assets
{

EventGenerator::GroundsOfObject EventGenerator::m_groundsOfObject;

EventGenerator::~EventGenerator()
{}

void EventGenerator::init()
{
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<EventGenerator>(this,
                &EventGenerator::ObjColl2OnSurface));
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<EventGenerator>(this,
                &EventGenerator::ObjColl2OnAir));
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<EventGenerator>(this,
                &EventGenerator::ObjColl2LadderEvents));
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
        Base::EventManager::process(new OnSurface(o1));
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
                Base::EventManager::process(new OnAir(of));
            }
        }
    }
    if (0 != os->component<Core::Physics>()) {
        if (m_groundsOfObject[os].size()) {
            m_groundsOfObject[os].remove(of);
            if (m_groundsOfObject[os].size() == 0) {
                Base::EventManager::process(new OnAir(os));
            }
        }
    }
}

void EventGenerator::ObjColl2LadderEvents(Base::Event* e)
{
    // TODO multiple ladders support
    Core::ObjectCollision* oc = Core::ObjectCollision::cast(e);
    assert(0 != oc);
    if (!oc->isTrigger()) {
        return;
    }
    const Core::LogicObject* o;
    const Core::LogicObject* l;
    if (oc->first()->typeName() == "ladder"  // TODO change hardcode
            && oc->second()->typeName() != "ladder") {
        o = oc->second();
        l = oc->first();
    } else if (oc->first()->typeName() != "ladder"
            && oc->second()->typeName() == "ladder") {
        o = oc->first();
        l = oc->second();
    } else {
        return;
    }
    if (oc->status() == Core::ObjectCollision::Status::Attached) {
        Base::EventManager::process(new OnLadderEvent(o, l));
    } else {
        Base::EventManager::process(new OutLadderEvent(o, l));
    }
}

} // namespace Assets
