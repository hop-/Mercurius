#ifndef _CORE_EVENT_HPP_
#define _CORE_EVENT_HPP_

#include <base/typed_base.hpp>

#include <vector>
#include <map>
#include <functional>
#include <cassert>

namespace Core
{

class Event
    : public Base::TypedBase
{
public:
    typedef void (*OnNotify) (Event*);
    using Callback = std::function<void(Event*)>;

public:
    virtual void trigger() = 0;
};

template <class T>
class EventCreator
    : public Event
{
private:
    static const ID type;
    typedef std::map<void*, std::vector<Callback>> Callbacks;
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

    template<class F, class OBJTYPE>
    static void registerCallback(F c, OBJTYPE* object)
    {
        using std::placeholders::_1;
        m_callbacks[object].push_back(std::bind(c, object, _1));
    }

    static void removeCallbacks(void* object)
    {
        m_callbacks[object].clear();
        m_callbacks.erase(object);
    }

    void trigger()
    {
        for (auto pair : m_callbacks) {
            for (auto& callback : pair.second) {
                assert(callback && "callback target is invalid");
                callback(this);
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

} // namespace Core

#endif //_CORE_EVENT_HPP_
