#ifndef _ASSETS_COMMANDS_HPP_
#define _ASSETS_COMMANDS_HPP_

#include <core/command.hpp>
#include <core/vector.hpp>

namespace Core
{

class LogicObject;

} // namespace Core

namespace Assets
{

class Accelerate
    : public Core::Command
{
    Core::LogicObject* m_object;
    Core::Vector m_acceleration;

public:
    Accelerate(Core::LogicObject* object, Core::Vector acceleration);
    void execute();
};

} // namespace Assets

#endif //_ASSETS_COMMANDS_HPP_
