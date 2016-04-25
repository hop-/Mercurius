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
    Command* onInit() override;
    Command* command() override;

private:
    void onKeyEvent(Event* e) override;
    void onObjectCollision(Event* e) override;
};

class OnLadder
    : public State
{
public:
    OnLadder();
    ~OnLadder();

public:
    Command* onInit() override;
    Command* command() override;

private:
    void onKeyEvent(Event* e) override;
    void onObjectCollision(Event* e) override;
};

class MoveOnLadder // better to use template
    : public State
{
    InputManager::Key m_stopKey;

public:
    MoveOnLadder(VerticalDirection d);
    ~MoveOnLadder();

public:
    Command* onInit() override;
    Command* command() override;

private:
    void onKeyEvent(Event* e) override;
    void onObjectCollision(Event* e) override;
};

class OnGround
    : public State
{
public:
    OnGround();
    ~OnGround();

public:
    Command* onInit() override;

private:
    void onKeyEvent(Event* e) override;
    void onAir(Event* e);
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
    Command* onInit() override;
    Command* command() override;

private:
    void onKeyEvent(Event* e) override;
    void onSurface(Event* e);
};

class Falling
    : public State
{
public:
    Falling();
    ~Falling();

public:
    Command* onInit() override;

private:
    void onSurface(Event* e);
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
    Command* onInit() override;
    Command* command() override;

private:
    void onKeyEvent(Event* e) override;
    void onObjectCollision(Event* e) override;
};

class LayerChanger
    : public State
{
private:
    bool m_is_active = false;

public:
    Command* command() override;

private:
    void onKeyEvent(Event* e) override;

};

} // namespace Core

#endif //_CORE_STATES_HPP_
