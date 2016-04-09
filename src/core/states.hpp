#ifndef _CORE_STATES_HPP_
#define _CORE_STATES_HPP_

#include "state.hpp"
#include "units.hpp"
#include "input_manager.hpp"

namespace Core
{

class Event;

class Standing
    : public State
{
public:
    virtual Command* onInit();
    void process(Event* e);
    Command* command();
};

class OnGround
    : public State
{
    int m_countOfGroundObjects = 1;

public:
    Command* onInit();
    void process(Event* e);
};

class Jumping
    : public State
{
    int m_count = 100;
    EngineUnit m_power = 25;

public:
    Jumping() = default;
    Jumping(EngineUnit power);

public:
    Command* onInit();
    void process(Event* e);
    Command* command();
};

class Falling
    : public State
{
public:
    Command* onInit();
    void process(Event* e);
};

class Running   // better to use template
    : public State
{
    HorizontalDirection m_direction;
    HorizontalDirection m_antiDirection;
    InputManager::Key m_changeDir;
    InputManager::Key m_stopRunning;

public:
    Running(HorizontalDirection d);

public:
    virtual Command* onInit();
    void process(Event* e);
    Command* command();
};

} // namespace Core

#endif //_CORE_STATES_HPP_
