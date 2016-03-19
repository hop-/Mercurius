#ifndef _CORE_STATE_HPP_
#define _CORE_STATE_HPP_

#include <base/object.hpp>

namespace Core
{

class Event;
class Command;

class State
    : public Base::Object
{
public:
    virtual void init() = 0;
    virtual void process(Event* e) = 0;
    virtual Command* command() const = 0;
};

} // namespace Core

#endif //_CORE_STATE_HPP_
