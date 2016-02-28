#ifndef _CORE_EVENT_HPP_
#define _CORE_EVENT_HPP_

#include <base/typed_base.hpp>

#include <cassert>

namespace Core
{

class Event
    : public Base::TypedBase
{};

template <class T>
class EventCreator
    : public Event
{
    static const ID type;

public:
    static bool castable(Event* e)
    {
        assert(0 != e);
        return e->getType() == type;
    }

    int getType() const
    {
        return type;
    }
};

template <class T>
const Event::ID EventCreator<T>::type;

} // namespace Core

#endif //_CORE_EVENT_HPP_
