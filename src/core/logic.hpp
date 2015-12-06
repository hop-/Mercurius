#ifndef _CORE_LOGIC_HPP_
#define _CORE_LOGIC_HPP_

namespace Core
{

class Logic
{
public:
    virtual ~Logic() = default;
    virtual void update() = 0;
};

} // namespace Core

#endif //_CORE_LOGIC_HPP_
