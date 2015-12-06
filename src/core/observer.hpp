#ifndef _CORE_OBSERVER_HPP_
#define _CORE_OBSERVER_HPP_

namespace Core
{

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onNotify() = 0;
};

} // namespace Core

#endif //_CORE_OBSERVER_HPP_
