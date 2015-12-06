#ifndef _CORE_COMMAND_HPP_
#define _CORE_COMMAND_HPP_

namespace Core
{

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

} // namespace Core

#endif //_CORE_COMMAND_HPP_
