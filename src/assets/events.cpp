#include "events.hpp"

namespace Assets
{

LadderEnter::LadderEnter(const Core::LogicObject* object
        , const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

LadderExit::LadderExit(const Core::LogicObject* object
        , const Core::LogicObject* ladder)
    : m_object(object)
    , m_ladder(ladder)
{}

OnLadderEvent::OnLadderEvent(const Core::LogicObject* object
        , const Core::VerticalDirection d)
    : m_object(object)
    , m_direction(d)
{}

AtTheDoor::AtTheDoor(const Core::LogicObject* door, bool status)
    : m_door(door)
    , m_status(status)
{}

} // namespace Assets
