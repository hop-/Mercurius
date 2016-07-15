#ifndef _CORE_STATE_HPP_
#define _CORE_STATE_HPP_

#include <base/object.hpp>

namespace Base
{

class Event;

}

namespace Core
{

class LogicObject;
class Command;

class State
    : public Base::Object
{
public:
    State();
    virtual ~State();
    void init() final;
    virtual Command* command();

protected:
    virtual Command* onInit();

protected:
    void addState(State* newState);
    void changeState(State* newState);
    void removeState(State* state);

protected:
    virtual void onKeyEvent(Base::Event*) {}
    virtual void onObjectCollision(Base::Event*) {}
};

} // namespace Core

#endif //_CORE_STATE_HPP_
