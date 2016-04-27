#ifndef _CORE_STATE_HPP_
#define _CORE_STATE_HPP_

#include <base/object.hpp>

namespace Base
{

class Event;

}

namespace Core
{

class Command;

class State
    : public Base::Object
{
public:
    State();
    virtual ~State();

    void init() final;

    virtual Command* command()
    {
        return 0;
    }

protected:
    virtual Command* onInit()
    {
        return 0;
    }

protected:
    virtual void onKeyEvent(Base::Event*)
    {}

    virtual void onObjectCollision(Base::Event*)
    {}
};

} // namespace Core

#endif //_CORE_STATE_HPP_
