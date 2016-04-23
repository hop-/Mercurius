#ifndef _ASSETS_COMMANDS_HPP_
#define _ASSETS_COMMANDS_HPP_

#include "command.hpp"
#include "vector.hpp"
#include "units.hpp"

namespace Core
{

class LogicObject;

class Accelerate
    : public Command
{
    Vector m_acceleration;

public:
    Accelerate(LogicObject* object, Vector acceleration);
    void execute();

private:
    Accelerate(const Core::Accelerate&) = delete;
    Accelerate& operator=(const Core::Accelerate&) = delete;
};

class Stop
    : public Command
{
    Direction m_direction;
public:
    Stop(LogicObject* object, Direction d);
    void execute();

private:
    Stop(const Stop&) = delete;
    Stop& operator=(const Stop&) = delete;
};

class SetYVelocity
    : public Command
{
    EngineUnit m_yVelocity;
    VerticalDirection m_direction;

public:
    SetYVelocity(LogicObject* object, EngineUnit v, VerticalDirection d);
    void execute();

private:
    SetYVelocity(const SetYVelocity&) = delete;
    SetYVelocity& operator=(const SetYVelocity&) = delete;
};

class Jump
    : public Command
{
    EngineUnit m_power;

public:
    Jump(LogicObject* object, EngineUnit power);
    void execute();

private:
    Jump(const Core::Jump&) = delete;
    Jump& operator=(const Core::Jump&) = delete;
};

class Stand
    : public Command
{

public:
    Stand(LogicObject* object);
    void execute();

private:
    Stand(const Core::Stand&) = delete;
    Stand& operator=(const Core::Stand&) = delete;
};

} // namespace Core

#endif //_CORE_COMMANDS_HPP_
