#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

namespace Core
{

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

} /// namespace Core

#endif //_COMMAND_HPP_
