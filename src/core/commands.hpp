#ifndef _ASSETS_COMMANDS_HPP_
#define _ASSETS_COMMANDS_HPP_

#include "command.hpp"
#include "vector.hpp"

namespace Core
{

class LogicObject;

class Accelerate
    : public Core::Command
{
    Core::LogicObject* m_object;
    Core::Vector m_acceleration;

public:
    Accelerate(Core::LogicObject* object, Core::Vector acceleration);
    void execute();
};

class Stand
    : public Core::Command
{
    Core::LogicObject* m_object;

public:
    Stand(Core::LogicObject* object);
    void execute();
};

} // namespace Core

#endif //_CORE_COMMANDS_HPP_
