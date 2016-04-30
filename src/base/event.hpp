#ifndef _BASE_EVENT_HPP_
#define _BASE_EVENT_HPP_

#include "delegate.hpp"
#include "typed_base.hpp"

#include <algorithm>
#include <list>
#include <cassert>

namespace Base
{

class Event
    : public Base::TypedBase
{
public:
    virtual void trigger() = 0;
};

template <class T>
class EventCreator
    : public Event
{
private:
    static const ID type;
    typedef std::list<Delegate*> Callbacks;
    static Callbacks m_callbacks;

protected:
    EventCreator() = default;
    EventCreator(const EventCreator&) = delete;
    EventCreator& operator=(const EventCreator&) = delete;

public:
    static bool castable(Event* e)
    {
        assert(0 != e);
        return e->getType() == type;
    }

    static T* cast(Event* e)
    {
        return (castable(e)) ? static_cast<T*>(e) : 0;
    }

    static void registerCallback(Delegate* delegate)
    {
        assert(0 != delegate);
        m_callbacks.push_back(delegate);
    }

    static void removeCallbacks(void* )
    {
/*        Callbacks::iterator i = std::find_if(m_callbacks.begin(), m_callbacks.end(), [&](Delegate* d) {
                assert(0 != d);
                return d->m_obj == object;
                });
        assert(i != m_callbacks.end());
        delete *i;
        m_callbacks.erase(i);*/
    }

    void trigger() override
    {
        for (Callbacks::iterator i = m_callbacks.begin(); i != m_callbacks.end() ; ++i) {
                assert(0 != *i);
                (*i)->invoke(this);
            }
    }

    int getType() const
    {
        return type;
    }
};

template <class T>
const Event::ID EventCreator<T>::type;

template <class T>
typename EventCreator<T>::Callbacks EventCreator<T>::m_callbacks;

} // namespace Base

#endif //_BASE_EVENT_HPP_
