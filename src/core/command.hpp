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
    Command(LogicObject* o)
        : m_object(o)
    {
        assert(0 != m_object);
    }

    virtual ~Command() = default;
    virtual void execute() = 0;

private:
    Command& operator=(const Command&) = delete;
    Command(const Command&) = delete;

protected:
    inline LogicObject* object()
    {
        return m_object;
    }
};

} // namespace Core

#endif //_CORE_COMMAND_HPP_
