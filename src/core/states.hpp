#ifndef _CORE_STATES_HPP_
#define _CORE_STATES_HPP_

#include "state.hpp"

namespace Core
{

class Event;

class Standing
    : public Core::State
{
public:
    virtual void init();
    void process(Core::Event* e);
    Core::Command* command() const;
};

class RunningLeft
    : public Core::State
{
public:
    virtual void init();
    void process(Core::Event* e);
    Core::Command* command() const;
};

class RunningRight
    : public Core::State
{
public:
    virtual void init();
    void process(Core::Event* e);
    Core::Command* command() const;
};

} // namespace Core

#endif //_CORE_STATES_HPP_
