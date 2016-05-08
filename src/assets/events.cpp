#include "events.hpp"

namespace Assets
{

LadderEnter::LadderEnter(const Core::LogicObject* object
        , const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

bool LadderEnter::less(Base::TypedBase* obj)
{
    return (this < obj);
}

LadderExit::LadderExit(const Core::LogicObject* object
        , const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

bool LadderExit::less(Base::TypedBase* obj)
{
    return (this < obj);
}

OnLadderEvent::OnLadderEvent(const Core::LogicObject* object
        , const Core::VerticalDirection d)
    : m_object(object)
    , m_direction(d)
{}

bool OnLadderEvent::less(Base::TypedBase* obj)
{
    return (this < obj);
}

} // namespace Assets
