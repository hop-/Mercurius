#ifndef _CORE_STATES_HPP_
#define _CORE_STATES_HPP_

#include "state.hpp"

namespace Core
{

class Event;

class Standing  // TODO now it is state manager
    : public State
{
public:
    virtual void init();
    void process(Event* e);
    Command* command();
};

class Jumping
    : public State
{
    int m_count = 100;

public:
    void init();
    void process(Event* e);
    Command* command();
};

class RunningLeft
    : public State
{
public:
    virtual void init();
    void process(Event* e);
    Command* command();
};

class RunningRight
    : public State
{
public:
    virtual void init();
    void process(Event* e);
    Command* command();
};

} // namespace Core

#endif //_CORE_STATES_HPP_
