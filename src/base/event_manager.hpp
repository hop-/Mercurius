#ifndef _BASE_EVENT_MANAGER_HPP_
#define _BASE_EVENT_MANAGER_HPP_

#include <vector>

namespace Base
{
class Event;

class EventManager // The class has been shortened, need more review
{
private:
    typedef std::vector<Base::Event*> Events;
    static Events m_deleteEvents;

private:
    EventManager() = delete;

public:
    static void processAllDeleteEvents();

public:
    static void processDeleteEvent(Base::Event* e);

public:
    static void process(Base::Event* e);
};

class InputHandler
{
public:
    virtual ~InputHandler() = default;

public:
    virtual unsigned getTicks() = 0;
    virtual void catchUserInput() = 0;
};

} // namespace Base

#endif //_BASE_EVENT_MANAGER_HPP_
