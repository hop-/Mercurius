#ifndef _ASSETS_STATES_HPP_
#define _ASSETS_STATES_HPP_

#include <core/state.hpp>

namespace Core
{
class Event;
}

namespace Assets
{

class Standing
    : public Core::State
{
public:
    virtual void init();
    void process(Core::Event* e);
};

class RunningLeft
    : public Core::State
{
public:
    virtual void init();
    void process(Core::Event* e);
};

class RunningRight
    : public Core::State
{
public:
    virtual void init();
    void process(Core::Event* e);
};

} // namespace Assets

#endif //_ASSETS_STATES_HPP_
