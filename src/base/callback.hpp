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
    void* m_object;

public:
    CallbackCreator(void* o, Delegate* d)
        : m_object(o)
    {
        assert(0 != m_object);
        assert(0 != d);
        T::registerCallback(m_object, d);
    }

    ~CallbackCreator()
    {
        T::removeCallbacks(m_object);
    }

public:
    void deactivate() override final
    {
        T::deactivate(m_object);
    }

private:
    CallbackCreator(const CallbackCreator&) = delete;
    CallbackCreator& operator=(const CallbackCreator&) = delete;
};

} // namespace Base

#endif //_BASE_CALLBACK_HPP_
