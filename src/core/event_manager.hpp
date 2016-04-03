#ifndef _CORE_EVENT_MANAGER_HPP_
#define _CORE_EVENT_MANAGER_HPP_

#include <list>
#include <cassert>

namespace Core
{

class Event;
class Layer;
class Command;

class EventManager
{
    std::list<Event*> m_eventQueue;
    std::list<Event*> m_waitingEvents;

public:
    EventManager();
    virtual ~EventManager() = default;

public:
    virtual void catchEvent() = 0;
    virtual unsigned getTicks() = 0;
    Event* getEvent();
    Command* getCommand(Layer*);
    void pop();

    inline void push(Event* e)
    {
        assert(0 != e);
        m_waitingEvents.push_back(e);
    }

protected:
    inline void pushToQueue(Event* e)
    {
        assert(0 != e);
        m_eventQueue.push_back(e);
    }
    inline void moveWaitingsToQueue()
    {
        m_eventQueue.insert(m_eventQueue.end()
                , m_waitingEvents.begin()
                , m_waitingEvents.end());
        m_waitingEvents.clear();
    }
};

} // namespace Core

#endif //_CORE_EVENT_MANAGER_HPP_
