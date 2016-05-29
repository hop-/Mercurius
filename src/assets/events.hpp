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

    inline const Core::LogicObject* object() const
    {
        return m_object;
    }

    inline const Core::LogicObject* ladder() const
    {
        return m_ladder;
    }

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

    inline const Core::LogicObject* object() const
    {
        return m_object;
    }

    inline const Core::LogicObject* ladder() const
    {
        return m_ladder;
    }

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

    inline const Core::LogicObject* object() const
    {
        return m_object;
    }

    inline Core::VerticalDirection direction() const
    {
        return m_direction;
    }

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

    inline bool status() const
    {
        return m_status;
    }

    inline const Core::LogicObject* door() const
    {
        return m_door;
    }

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

    inline bool status() const
    {
        return m_status;
    }

    inline const Core::LogicObject* switchObject() const
    {
        return m_switch;
    }

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

    inline const Core::LogicObject* switchObject() const
    {
        return m_switch;
    }

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
    MakeTriggerForPlatforms(const Core::LogicObject* object, bool status)
        : m_object(object)
        , m_status(status)
    {}

    inline const Core::LogicObject* object() const
    {
        return m_object;
    }

    inline bool status() const
    {
        return m_status;
    }

private:
    MakeTriggerForPlatforms(const MakeTriggerForPlatforms&) = delete;
    MakeTriggerForPlatforms& operator=(const MakeTriggerForPlatforms&) = delete;
};

} // namespace Assets

#endif //_ASSETS_EVENTS_HPP_
