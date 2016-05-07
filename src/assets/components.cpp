#include "components.hpp"
#include "events.hpp"

#include <core/events.hpp>

#include <base/delegate.hpp>
#include <base/event_manager.hpp>

namespace Assets
{

LadderZone::LadderZone()
{
    registerCallback<Core::ObjectCollision>(
            new Base::DelegateCreator<LadderZone>(this
                , &LadderZone::onObjectCollision));
}

void LadderZone::onObjectCollision(Base::Event* e)
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

} // namespace Assets
