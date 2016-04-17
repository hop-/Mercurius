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
    int a = 12;

public:
    Standing();
    ~Standing();

public:
    Command* onInit();
    Command* command();

private:
    void onKeyEvent(Event* e);
    void onObjectCollision(Event* e);
};

class OnLadder
    : public State
{
public:
    OnLadder();
    ~OnLadder();

public:
    Command* onInit();

private:
    void onKeyEvent(Event* e);
    void onObjectCollision(Event* e);
};

class MoveOnLadder // better to use template
    : public State
{
    InputManager::Key m_stopKey;

public:
    MoveOnLadder(VerticalDirection d);
    ~MoveOnLadder();

public:
    Command* onInit();
    Command* command();

private:
    void onKeyEvent(Event* e);
    void onObjectCollision(Event* e);
};

class OnGround
    : public State
{
    int m_countOfGroundObjects = 1;

public:
    OnGround();
    ~OnGround();

public:
    Command* onInit();

private:
    void onKeyEvent(Event* e);
    void onObjectCollision(Event* e);
};

class Jumping
    : public State
{
    int m_count = 100;
    EngineUnit m_power = 25;

public:
    Jumping();
    Jumping(EngineUnit power);
    ~Jumping();

public:
    Command* onInit();
    Command* command();

private:
    void onKeyEvent(Event* e);
    void onObjectCollision(Event* e);
};

class Falling
    : public State
{
public:
    Falling();
    ~Falling();

public:
    Command* onInit();

private:
    void onObjectCollision(Event* e);
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
    ~Running();

public:
    virtual Command* onInit();
    Command* command();

private:
    void onKeyEvent(Event* e);
    void onObjectCollision(Event* e);
};

} // namespace Core

#endif //_CORE_STATES_HPP_
