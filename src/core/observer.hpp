#ifndef _OBSERVER_HPP_
#define _OBSERVER_HPP_

namespace Core
{

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onNotify() = 0;
};

} /// namespace Core

#endif //_OBSERVER_HPP_
