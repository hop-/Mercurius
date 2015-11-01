#ifndef _LOGIC_HPP_
#define _LOGIC_HPP_

namespace Core
{

class Logic
{
public:
    virtual ~Logic() = default;
    virtual void update() = 0;
};

} // namespace Core

#endif //_LOGIC_HPP_
