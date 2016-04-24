#ifndef _CORE_EVENT_MANAGER_HPP_
#define _CORE_EVENT_MANAGER_HPP_

namespace Core
{

class Event;
class Layer;
class Command;

class EventManager // The class has been shortened, need more review
{
private:
    EventManager() = delete;

public:
    static void process(Event* e);
};

class InputHandler
{
public:
    virtual ~InputHandler() = default;

public:
    virtual unsigned getTicks() = 0;
    virtual void catchUserInput() = 0;
};

} // namespace Core

#endif //_CORE_EVENT_MANAGER_HPP_
