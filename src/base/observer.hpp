#ifndef _BASE_OBSERVER_HPP_
#define _BASE_OBSERVER_HPP_

namespace Base
{

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void onNotify() = 0;
};

} // namespace Base

#endif //_BASE_OBSERVER_HPP_
