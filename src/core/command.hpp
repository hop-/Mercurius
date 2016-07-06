#ifndef _CORE_COMMAND_HPP_
#define _CORE_COMMAND_HPP_

#include <cassert>

namespace Core
{

class LogicObject;

class Command
{
private:
    LogicObject* m_object;

public:
    Command(LogicObject* o);
    virtual ~Command() = default;

public:
    virtual void execute() = 0;

private:
    Command& operator=(const Command&) = delete;
    Command(const Command&) = delete;

protected:
    LogicObject* object();
};

} // namespace Core

#endif //_CORE_COMMAND_HPP_
