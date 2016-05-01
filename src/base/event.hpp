#ifndef _BASE_EVENT_HPP_
#define _BASE_EVENT_HPP_

#include "delegate.hpp"
#include "typed_base.hpp"

#include <algorithm>
#include <list>
#include <map>
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
    typedef std::map<void*, std::list<Delegate*> > Callbacks;
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

    static void registerCallback(void* o, Delegate* delegate)
    {
        assert(0 != delegate);
        assert(0 != o);
        m_callbacks[o].push_back(delegate);
    }

    static void removeCallbacks(void* o)
    {
        assert(m_callbacks.find(o) != m_callbacks.end());
        for (auto& i : m_callbacks[o]) {
            delete i;
        }
        m_callbacks.erase(o);
    }
    static void deactivate(void* o)
    {
        assert(m_callbacks.find(o) != m_callbacks.end());
        for (auto& i : m_callbacks[o]) {
            i->deactivate();
        }
    }

    void trigger() override
    {
        for (auto& pair : m_callbacks) {
                for (auto& callback: pair.second) {
                    assert(0 != callback);
                    callback->invoke(this);
                }
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
