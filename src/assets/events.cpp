#include "events.hpp"

namespace Assets
{

OnLadderEvent::OnLadderEvent(const Core::LogicObject* object
        , const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

bool OnLadderEvent::less(Base::TypedBase* obj)
{
    return (this < obj);
}

OutLadderEvent::OutLadderEvent(const Core::LogicObject* object
        , const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

bool OutLadderEvent::less(Base::TypedBase* obj)
{
    return (this < obj);
}

} // namespace Assets
