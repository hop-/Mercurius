#ifndef _ASSETS_EVENTS_HPP_
#define _ASSETS_EVENTS_HPP_

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

    bool less(Base::TypedBase* obj) override;
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

    bool less(Base::TypedBase* obj) override;
};

} // namespace Assets

#endif //_ASSETS_EVENTS_HPP_
