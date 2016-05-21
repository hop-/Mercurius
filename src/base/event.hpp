#ifndef _BASE_EVENT_HPP_
#define _BASE_EVENT_HPP_

#include "delegate.hpp"
#include "typed_base.hpp"

#include <algorithm>
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
    static int m_callbackID;
    typedef std::map<int, Delegate*> Callbacks;
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

    static T* uncheckedCast(Event* e)
    {
        assert(0 != e);
        assert(static_cast<T*>(e));
        return static_cast<T*>(e);
    }

    static int registerCallback(Delegate* delegate)
    {
        assert(0 != delegate);
        assert(m_callbacks.find(m_callbackID) == m_callbacks.end());
        m_callbacks[m_callbackID] = delegate;
        return m_callbackID++;
    }

    static void removeCallbacks(int id)
    {
        assert(m_callbacks.find(id) != m_callbacks.end());
        delete m_callbacks[id];
        m_callbacks.erase(id);
    }
    static void deactivate(int id)
    {
        assert(m_callbacks.find(id) != m_callbacks.end());
        m_callbacks[id]->deactivate();
    }

    void trigger() override
    {
        for (auto& pair : m_callbacks) {
            assert(0 != pair.second);
            pair.second->invoke(this);
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
int EventCreator<T>::m_callbackID = 0;

template <class T>
typename EventCreator<T>::Callbacks EventCreator<T>::m_callbacks;

} // namespace Base

#endif //_BASE_EVENT_HPP_
