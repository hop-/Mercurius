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
public:
    NearLadder();

private:
    void onKeyEvent(Base::Event* e) override;
    virtual void outLadder(Base::Event* e);
};

class OnLadder
    : public NearLadder
{
public:
    OnLadder();

public:
    Core::Command* onInit() override;
    Core::Command* command() override;
private:
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
};

class OnGround
    : public Core::State
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
    : public Core::State
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
    : public Core::State
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

} // namespace Assets

#endif //_ASSETS_STATES_HPP_
