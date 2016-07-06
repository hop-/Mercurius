#ifndef _ASSETS_EVENTS_HPP_
#define _ASSETS_EVENTS_HPP_

#include <core/units.hpp>

#include <base/event.hpp>

namespace Core
{
class LogicObject;
}

namespace Assets
{

class LadderEnter
    : public Base::EventCreator<LadderEnter>
{
    const Core::LogicObject* m_object;
    const Core::LogicObject* m_ladder;

public:
    LadderEnter(const Core::LogicObject* object
            , const Core::LogicObject* ladder);

public:
    const Core::LogicObject* object() const;
    const Core::LogicObject* ladder() const;

private:
    LadderEnter(const LadderEnter&) = delete;
    LadderEnter& operator=(const LadderEnter&) = delete;
};

class LadderExit
    : public Base::EventCreator<LadderExit>
{
    const Core::LogicObject* m_object;
    const Core::LogicObject* m_ladder;

public:
    LadderExit(const Core::LogicObject* object
            , const Core::LogicObject* ladder);

public:
    const Core::LogicObject* object() const;
    const Core::LogicObject* ladder() const;

private:
    LadderExit(const LadderExit&) = delete;
    LadderExit& operator=(const LadderExit&) = delete;
};

class OnLadderEvent
    : public Base::EventCreator<OnLadderEvent>
{
    const Core::LogicObject* m_object;
    const Core::VerticalDirection m_direction;

public:
    OnLadderEvent(const Core::LogicObject* object
            , const Core::VerticalDirection d);

public:
    const Core::LogicObject* object() const;
    Core::VerticalDirection direction() const;

private:
    OnLadderEvent(const OnLadderEvent&) = delete;
    OnLadderEvent& operator=(const OnLadderEvent&) = delete;
};

class AtTheDoor
    : public Base::EventCreator<AtTheDoor>
{
    const Core::LogicObject* m_door;
    bool m_status;

public:
    AtTheDoor(const Core::LogicObject* door, bool status);

public:
    bool status() const;
    const Core::LogicObject* door() const;

private:
    AtTheDoor(const AtTheDoor&) = delete;
    AtTheDoor& operator=(const AtTheDoor&) = delete;
};

class AtTheSwitch
    : public Base::EventCreator<AtTheSwitch>
{
    const Core::LogicObject* m_switch;
    bool m_status;

public:
    AtTheSwitch(const Core::LogicObject* s, bool status);

public:
    bool status() const;
    const Core::LogicObject* switchObject() const;

private:
    AtTheSwitch(const AtTheSwitch&) = delete;
    AtTheSwitch& operator=(const AtTheSwitch) = delete;
};

class ToggleTheSwitch
    : public Base::EventCreator<ToggleTheSwitch>
{
    const Core::LogicObject* m_switch;

public:
    ToggleTheSwitch(const Core::LogicObject* s);

public:
    const Core::LogicObject* switchObject() const;

private:
    ToggleTheSwitch(const ToggleTheSwitch&) = delete;
    ToggleTheSwitch& operator=(const ToggleTheSwitch&) = delete;
};

class MakeTriggerForPlatforms
    : public Base::EventCreator<MakeTriggerForPlatforms>
{
    const Core::LogicObject* m_object;
    bool m_status;

public:
    MakeTriggerForPlatforms(const Core::LogicObject* object, bool status);

public:
    const Core::LogicObject* object() const;
    bool status() const;

private:
    MakeTriggerForPlatforms(const MakeTriggerForPlatforms&) = delete;
    MakeTriggerForPlatforms& operator=(const MakeTriggerForPlatforms&) = delete;
};

} // namespace Assets

#endif //_ASSETS_EVENTS_HPP_
