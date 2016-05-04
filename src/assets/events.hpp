#ifndef _ASSETS_EVENTS_HPP_
#define _ASSETS_EVENTS_HPP_

#include <base/event.hpp>

namespace Core
{
class LogicObject;
}

namespace Assets
{

class OnLadderEvent
    : public Base::EventCreator<OnLadderEvent>
{
    const Core::LogicObject* m_object;
    const Core::LogicObject* m_ladder;

public:
    OnLadderEvent(const Core::LogicObject* object
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
    OnLadderEvent(const OnLadderEvent&) = delete;
    OnLadderEvent& operator=(const OnLadderEvent&) = delete;

    bool less(Base::TypedBase* obj) override;
};

class OutLadderEvent
    : public Base::EventCreator<OutLadderEvent>
{
    const Core::LogicObject* m_object;
    const Core::LogicObject* m_ladder;

public:
    OutLadderEvent(const Core::LogicObject* object
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
    OutLadderEvent(const OutLadderEvent&) = delete;
    OutLadderEvent& operator=(const OutLadderEvent&) = delete;

    bool less(Base::TypedBase* obj) override;
};

} // namespace Assets

#endif //_ASSETS_EVENTS_HPP_
