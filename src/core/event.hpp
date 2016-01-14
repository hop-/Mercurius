#ifndef _CORE_EVENT_HPP_
#define _CORE_EVENT_HPP_

#include "typed_base.hpp"

#include <cassert>

namespace Core
{

class Event
    : public TypedBase
{};

template <class T>
class EventCreator
    : public Event
{
    static const ID type;

public:
    int getType() const
    {
        return type;
    }
};

template <class T>
const Event::ID EventCreator<T>::type;

} // namespace Core

#endif //_CORE_EVENT_HPP_
