#include "events.hpp"

namespace Assets
{

LadderEnter::
LadderEnter(const Core::LogicObject* object,
            const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

const Core::LogicObject* LadderEnter::
object() const
{
    return m_object;
}

const Core::LogicObject* LadderEnter::
ladder() const
{
    return m_ladder;
}

LadderExit::
LadderExit(const Core::LogicObject* object,
           const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

const Core::LogicObject* LadderExit::
object() const
{
    return m_object;
}

const Core::LogicObject* LadderExit::
ladder() const
{
    return m_ladder;
}

OnLadderEvent::
OnLadderEvent(const Core::LogicObject* object,
              const Core::VerticalDirection d)
    : m_object(object)
    , m_direction(d)
{}

const Core::LogicObject* OnLadderEvent::
object() const
{
    return m_object;
}

Core::VerticalDirection OnLadderEvent::
direction() const
{
    return m_direction;
}

AtTheDoor::
AtTheDoor(const Core::LogicObject* door, bool status)
    : m_door(door)
    , m_status(status)
{}

bool AtTheDoor::
status() const
{
    return m_status;
}

const Core::LogicObject* AtTheDoor::
door() const
{
    return m_door;
}

AtTheSwitch::
AtTheSwitch(const Core::LogicObject* s, bool status)
    : m_switch(s)
    , m_status(status)
{}

bool AtTheSwitch::
status() const
{
    return m_status;
}

const Core::LogicObject* AtTheSwitch::
switchObject() const
{
    return m_switch;
}

ToggleTheSwitch::
ToggleTheSwitch(const Core::LogicObject* s)
    : m_switch(s)
{}

const Core::LogicObject* ToggleTheSwitch::
switchObject() const
{
    return m_switch;
}

MakeTriggerForPlatforms::
MakeTriggerForPlatforms(const Core::LogicObject* object,
                        bool status)
    : m_object(object)
    , m_status(status)
{}

const Core::LogicObject* MakeTriggerForPlatforms::
object() const
{
    return m_object;
}

bool MakeTriggerForPlatforms::
status() const
{
    return m_status;
}

} // namespace Assets
