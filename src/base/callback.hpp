#ifndef _BASE_CALLBACK_HPP_
#define _BASE_CALLBACK_HPP_

#include <cassert>

namespace Base
{

class Delegate;

class Callback
{
public:
    virtual ~Callback() = default;
    virtual void deactivate() = 0;
};

template <class T>
class CallbackCreator
    : public Callback
{
    int m_id = 0;

public:
    CallbackCreator(Delegate* d)
    {
        assert(0 != d);
        m_id = T::registerCallback(d);
    }

    ~CallbackCreator()
    {
        T::removeCallbacks(m_id);
    }

public:
    void deactivate() override final
    {
        T::deactivate(m_id);
    }

private:
    CallbackCreator(const CallbackCreator&) = delete;
    CallbackCreator& operator=(const CallbackCreator&) = delete;
};

} // namespace Base

#endif //_BASE_CALLBACK_HPP_
