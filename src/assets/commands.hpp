#ifndef _ASSETS_COMMANDS_HPP_
#define _ASSETS_COMMANDS_HPP_

#include <core/command.hpp>
#include <core/vector.hpp>
#include <core/units.hpp>

namespace Core
{

class LogicObject;

}

namespace Assets
{

class Accelerate
    : public Core::Command
{
    Core::Vector m_acceleration;

public:
    Accelerate(Core::LogicObject* object, Core::Vector acceleration);
    void execute();

private:
    Accelerate(const Accelerate&) = delete;
    Accelerate& operator=(const Accelerate&) = delete;
};

class Stop
    : public Core::Command
{
    Core::Direction m_direction;
public:
    Stop(Core::LogicObject* object, Core::Direction d);
    void execute();

private:
    Stop(const Stop&) = delete;
    Stop& operator=(const Stop&) = delete;
};

class SetYVelocity
    : public Core::Command
{
    Core::EngineUnit m_yVelocity;
    Core::VerticalDirection m_direction;

public:
    SetYVelocity(Core::LogicObject* object, Core::EngineUnit v, Core::VerticalDirection d);
    void execute();

private:
    SetYVelocity(const SetYVelocity&) = delete;
    SetYVelocity& operator=(const SetYVelocity&) = delete;
};

class ApplyMovement
    : public Core::Command
{
    Core::EngineUnit m_velocity;
    Core::Direction m_direction;

public:
    ApplyMovement(Core::LogicObject* object
            , Core::EngineUnit v
            , Core::Direction d);
    void execute();

private:
    ApplyMovement(const ApplyMovement&) = delete;
    ApplyMovement& operator=(const ApplyMovement&) = delete;
};

class Jump
    : public Core::Command
{
    Core::EngineUnit m_power;

public:
    Jump(Core::LogicObject* object, Core::EngineUnit power);
    void execute();

private:
    Jump(const Jump&) = delete;
    Jump& operator=(const Jump&) = delete;
};

class Stand
    : public Core::Command
{

public:
    Stand(Core::LogicObject* object);
    void execute();

private:
    Stand(const Stand&) = delete;
    Stand& operator=(const Stand&) = delete;
};

} // namespace Assets

#endif //_ASSETS_COMMANDS_HPP_
