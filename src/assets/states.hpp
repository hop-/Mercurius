#ifndef _ASSETS_STATES_HPP_
#define _ASSETS_STATES_HPP_

#include <core/state.hpp>
#include <core/units.hpp>
#include <core/input_manager.hpp>

namespace Base
{

class Event;

}

namespace Assets
{

class Standing
    : public Core::State
{
public:
    Standing();

public:
    Core::Command* onInit() override;
    Core::Command* command() override;

private:
    void onKeyEvent(Base::Event* e) override;
    void onLadder(Base::Event* e);
};

class NearLadder
    : public Core::State
{
    const Core::LogicObject* m_ladder;

public:
    NearLadder(const Core::LogicObject* ladder);
    ~NearLadder();

private:
    NearLadder(const NearLadder&) = delete;
    NearLadder& operator=(const NearLadder&) = delete;

private:
    void onKeyEvent(Base::Event* e) override;
    virtual void outLadder(Base::Event* e);
};

class OnLadder
    : public Core::State
{
public:
    OnLadder();

public:
    Core::Command* onInit() override;
    Core::Command* command() override;
private:
    void onKeyEvent(Base::Event* e) override;
    virtual void outLadder(Base::Event* e);
    virtual void onKeyEvent2(Base::Event* e);
};

class MoveOnLadder // better to use template
    : public OnLadder
{
    Core::InputManager::Key m_stopKey;

public:
    MoveOnLadder(Core::VerticalDirection d);

public:
    Core::Command* onInit() override;
    Core::Command* command() override;

private:
    void onKeyEvent(Base::Event* e) override;
    void onSurface(Base::Event* e);
};

class VerticalMovementState
    : public Core::State
{
public:
    VerticalMovementState();

private:
    void registerOnLadder();
    virtual void onLadder(Base::Event* e);
};

class OnGround
    : public VerticalMovementState
{
public:
    OnGround();

public:
    Core::Command* onInit() override;

private:
    void onKeyEvent(Base::Event* e) override;
    void onAir(Base::Event* e);
};

class Jumping
    : public VerticalMovementState
{
    int m_count = 100;
    Core::EngineUnit m_power = 20;

public:
    Jumping();
    Jumping(Core::EngineUnit power);

public:
    Core::Command* onInit() override;
    Core::Command* command() override;

private:
    void onKeyEvent(Base::Event* e) override;
    void onSurface(Base::Event* e);
};

class Falling
    : public VerticalMovementState
{
public:
    Falling();

public:
    Core::Command* onInit() override;

private:
    void onSurface(Base::Event* e);
};

class Running   // better to use template
    : public Core::State
{
    Core::HorizontalDirection m_direction;
    Core::HorizontalDirection m_antiDirection;
    Core::InputManager::Key m_changeDir;
    Core::InputManager::Key m_stopRunning;

public:
    Running(Core::HorizontalDirection d);

public:
    Core::Command* onInit() override;
    Core::Command* command() override;

private:
    void onKeyEvent(Base::Event* e) override;
    void onLadder(Base::Event* e);
};

class LayerChanger
    : public Core::State
{
private:
    bool m_is_active = false;

public:
    Core::Command* command() override;

private:
    void onKeyEvent(Base::Event* e) override;
};

class SwitchInactive
    : public Core::State
{
public:
    SwitchInactive();

public:
    Core::Command* onInit() override;

private:
    void atTheSwitch(Base::Event* e);
};

class SwitchActive
    : public Core::State
{
public:
    SwitchActive();

public:
    Core::Command* onInit() override;

private:
    void onKeyEvent(Base::Event* e) override;
    void atTheSwitch(Base::Event* e);
};

class SwitchState
    : public Core::State
{
    bool m_status;

public:
    SwitchState(bool status);

public:
    Core::Command* onInit() override;

private:
    void onToggle(Base::Event* e);
};

class EnemyMove
    : public Core::State
{
    Core::HorizontalDirection m_direction;

public:
    EnemyMove(Core::HorizontalDirection direction);

public:
    Core::Command* onInit() override;
    Core::Command* command() override;

private:
    void onObjectCollision(Base::Event* e);
};

} // namespace Assets

#endif //_ASSETS_STATES_HPP_
