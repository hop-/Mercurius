#ifndef _CORE_EVENT_MANAGER_HPP_
#define _CORE_EVENT_MANAGER_HPP_

#include <queue>
#include <cassert>

namespace Core
{

class Event;
class Layer;
class Command;

class EventManager
{
    std::queue<Event*> m_eventQueue;

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
        m_eventQueue.push(e);
    }
};

} // namespace Core

#endif //_CORE_EVENT_MANAGER_HPP_
