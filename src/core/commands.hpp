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
    LogicObject* m_object;
    Vector m_acceleration;

public:
    Accelerate(LogicObject* object, Vector acceleration);
    void execute();
};

class Jump
    : public Command
{
    LogicObject* m_object;
    EngineUnit m_power;

public:
    Jump(LogicObject* object, EngineUnit power);
    void execute();
};

class Stand
    : public Command
{
    LogicObject* m_object;

public:
    Stand(LogicObject* object);
    void execute();
};

} // namespace Core

#endif //_CORE_COMMANDS_HPP_
