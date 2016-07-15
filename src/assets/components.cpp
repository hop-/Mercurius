#include "components.hpp"
#include "events.hpp"
#include "states.hpp"

#include <core/events.hpp>
#include <core/components.hpp>

#include <base/delegate.hpp>
#include <base/event_manager.hpp>

#include <debug/log.hpp>

namespace Assets
{

LadderZone::
LadderZone()
{
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<LadderZone>(this
                , &LadderZone::onObjectCollision));
}

void LadderZone::
onObjectCollision(Base::Event* e)
{
    Core::ObjectCollision* oc = Core::ObjectCollision::cast(e);
    assert(0 != oc);
    Core::LogicObject* owner = Component::parent();
    if (!oc->contains(owner)
            || oc->another(owner)->typeName() != "dude") { // hardcode
        return;
    }
    if (oc->status() == Core::ObjectCollision::Status::Attached) {
        Base::EventManager::process(
                new LadderEnter(oc->another(owner), owner));
    } else {
        Base::EventManager::process(
                new LadderExit(oc->another(owner), owner));
    }
}

DoorZone::
DoorZone()
{
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<DoorZone>(this
                , &DoorZone::onObjectCollision));
}

void DoorZone::
onObjectCollision(Base::Event* e)
{
    Core::ObjectCollision* oc = Core::ObjectCollision::cast(e);
    assert(0 != oc);
    const Core::LogicObject* owner = Component::parent();
    if (!oc->contains(owner)
            || oc->another(owner)->typeName() != "dude") { // hardcode
        return;
    }
    Base::EventManager::process(new AtTheDoor(oc->another(owner)
              , (oc->status() == Core::ObjectCollision::Status::Attached)));
}

SwitchZone::
SwitchZone()
{
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<SwitchZone>(this
                , &SwitchZone::onObjectCollision));
}

void SwitchZone::
onObjectCollision(Base::Event* e)
{
    Core::ObjectCollision* oc = Core::ObjectCollision::cast(e);
    assert(0 != oc);
    const Core::LogicObject* owner = Component::parent();
    if (!oc->contains(owner)
            || oc->another(owner)->typeName() != "dude") { // hardcode
        return;
    }
    Base::EventManager::process(new AtTheSwitch(oc->another(owner)
              , (oc->status() == Core::ObjectCollision::Status::Attached)));
}

PlatformZone::
PlatformZone()
{
    registerCallback<MakeTriggerForPlatforms>(
            new Base::DelegateCreator<PlatformZone>(this
                , &PlatformZone::makeTrigger));
}

void PlatformZone::
makeTrigger(Base::Event* e)
{
    MakeTriggerForPlatforms* mt = MakeTriggerForPlatforms::cast(e);
    assert(0 != mt);
    assert(0 != parent()->component<Core::Collider>());
    if (mt->status()) {
        parent()->component<Core::Collider>()
            ->addTriggerObject(mt->object());
    } else {
        parent()->component<Core::Collider>()
            ->removeTriggerObject(mt->object());
    }
}

void CameraFollower::
init()
{
    Core::ViewPort::getInstance()->addObserver(this);
}

void CameraFollower::
onNotify()
{
    Core::ViewPort* vp = static_cast<Core::ViewPort*>(subject());
    assert(0 != vp);
    move(vp->position());
}

void CameraFollower::
move(Core::Position p)
{
    Core::Position dp = p - m_viewPortLastPosition;
    m_viewPortLastPosition = p;
    Core::Position parentPosition = parent()->position();
    Core::Vector moveVector;
    moveVector.setX(dp.x() * m_velocityScaleX);
    moveVector.setY(dp.y() * m_velocityScaleY);
    parentPosition.move(moveVector);
    //parent()->setPosition(parentPosition); // TODO seg fault
}


void BeingController::
init()
{
    parent()->addState(new EnemyMove(Core::HorizontalDirection::Left));
}

} // namespace Assets
