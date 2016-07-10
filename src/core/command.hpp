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
    /**
     * @brief Base class for commands
     * @param o pointer to logic object
    */

    // TODO investigate, as to me LogicObject should not pass to Base Command
    Command(LogicObject* o);
    virtual ~Command() = default;

public:
    /**
     * @brief Executes command pure virtual
     */
    virtual void execute() = 0;

private:
    Command& operator=(const Command&) = delete;
    Command(const Command&) = delete;

protected:
    LogicObject* object();
};

} // namespace Core

#endif //_CORE_COMMAND_HPP_
